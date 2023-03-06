/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/05 20:08:58 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	here_doc(t_redire *redir, char **env)
{
	int			fd;
	char		*str;
	// static int	i;

	// signal(SIGINT, SIG_DFL);
	// printf("ZID\n");

	fd = open("tz", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("minishell");
		return ;
	}
	str = readline("> ");
	while (str && ft_strncmp(str, redir->delimiter, ft_strlen(redir->delimiter)))
	{
		// printf("%d\n", redir->quotes);
		if (!redir->quotes)
			str = expand_env(str, env);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	// unlink("tz");
	close(fd);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

int	exec_redir_in(char *infile, int *in)
{
	if (access(infile, F_OK) == 0)
	{
		close(*in);
		*in = open(infile, O_RDONLY, 0666);
		return (1);
	}
	else
	{
		*in = -1;
		write(2, "minishell: ", 11);
		ft_perror(infile, ": No such file or directory");
		return (0);
	}
}

void	exec_redir(t_redire *redir, t_fd *fd)
{
	t_redire	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == INFILE)
			exec_redir_in(tmp->infile, &fd->in);
		else if (tmp->type == OUTFILE)
		{
			close(fd->out);
			fd->out = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		else if (tmp->type == APPEND)
		{
			close(fd->out);
			fd->out = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		tmp = tmp->next;
	}
}

void	check_fd(t_cmd *cmd)
{
	if (cmd->fd.in != 0)
	{
		dup2(cmd->fd.in, STDIN_FILENO);
		close(cmd->fd.in);
	}
	if (cmd->fd.out != 1)
	{
		dup2(cmd->fd.out, STDOUT_FILENO);
		close(cmd->fd.out);
	}
}

void	error(char *str, int n)
{
	if (str)
	{
		ft_putstr_fd(strerror(n), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(n);
}

char	*get_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	if (ft_strchrr(cmd, '/'))
		return (cmd);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	**get_paths(char **env, t_shell *shell)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				error("Split function failed", 1);
			return (paths);
		}
		i++;
	}
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(*shell->cmds, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
	return (NULL);
}

void	ft_execute(t_shell *shell, char **env)
{
	pid_t	pid;
	char	**paths = NULL;
	char	*argv = NULL;
	int	success;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		if (shell->redir)
		{
			success = exec_redir_in(shell->redir->infile, &shell->cmd->fd.in);
			if (!success)
				exit(1);
			exec_redir(shell->redir, &shell->cmd->fd);
		}
		check_fd(shell->cmd);
		paths = get_paths(env, shell);
		argv = get_cmd(paths, shell->cmds[0]);
		if (!argv)
		{
			free_paths(paths);
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(ft_strtrim(shell->cmds[0], "\""), 2);
			ft_putstr_fd(": Command not found", 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
		if (execve(argv, shell->cmds, env) == -1)
			error(NULL, errno);
	}
	if (shell->cmd->fd.in != 0)
		close(shell->cmd->fd.in);
	if (shell->cmd->fd.out != 1)
		close(shell->cmd->fd.out);
	waitpid(pid, NULL, 0);
}

int	check_builtins(char *cmd)
{
	if (cmd && !ft_strcmp(cmd, "export"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "unset"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "pwd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "exit"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "cd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "env"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

void	ft_which_cmd(char **cmd, t_env *env)
{
	if (cmd[0] && !ft_strcmp(cmd[0], "export"))
		export_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "unset"))
		unset_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "pwd"))
		pwd_builtin(*cmd);
	else if (cmd[0] && !ft_strcmp(cmd[0], "exit"))
		exit_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "cd"))
		cd_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "env"))
		env_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "echo"))
		echo_builtin(cmd);
}

void	execute_builtin(t_shell *shell, t_env *env)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (shell->redir)
		exec_redir(shell->redir, &shell->cmd->fd);
	if (shell->cmd->fd.in == -1)
	{
		//status = 1;
		return ;
	}
	check_fd(shell->cmd);
	ft_which_cmd(shell->cmds, env);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

int	ft_lstsize(t_shell *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	open_heredocs(t_shell *shell, t_env *env)
{
	t_shell	*tmp;

	tmp = shell;
	while (tmp)
	{
		while (tmp->redir)
		{
			if (tmp->redir->type == DELIMITER)
				here_doc(tmp->redir, env->env);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
}

int	exec_builtins_execve(t_shell *shell, t_env *env)
{
	// exec_redir(shell->redir, &shell->cmd->fd, env->env);
	open_heredocs(shell, env);
	// if (check_builtins(shell->cmds[0]) == 1)
	// 	execute_builtin(shell, env);
	// else
	// {
	// 	// printf("1zid\n");
	// 	ft_execute(shell, env->env);
	// }
	return (0);
}

void	dup_close(int *fd1, int fd2)
{
	dup2(*fd1, fd2);
	close(*fd1);
}

void	execute_cmd(t_shell *shell, char **env)
{
	char	**paths = NULL;
	char	*argv = NULL;

	paths = get_paths(env, shell);
	argv = get_cmd(paths, shell->cmds[0]);
	if (!argv)
	{
		free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(ft_strtrim(shell->cmds[0], "\""), 2);
		ft_putstr_fd(": Command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(argv, shell->cmds, env) == -1)
		error(NULL, errno);
}

void	child(t_shell *shell, t_env *env, int fd[2])
{
	exec_redir(shell->redir, &shell->cmd->fd);
	check_fd(shell->cmd);
	if (shell->next)
		dup_close(&fd[1], 1);
	if (shell->cmd->fd.in == 0)
		dup_close(&fd[0], 0);
	if (check_builtins(shell->cmds[0]))
		ft_which_cmd(shell->cmds, env);
	else
		execute_cmd(shell, env->env);
	exit(EXIT_SUCCESS);
}

void	parent(t_shell *shell, int fd[2])
{
	if (!shell->next)
		close(fd[0]);
	if (shell && shell->redir && shell->redir->outfile)
		close(shell->cmd->fd.out);
	if (shell && shell->redir && shell->redir->infile)
		close(shell->cmd->fd.in);
	close(fd[1]);
}

void	execute(t_shell *shell, t_env *env)
{
	// int		fd[2];
	// pid_t	id;

	
	// if (ft_lstsize(shell) == 1)
		exec_builtins_execve(shell, env);
	// else
	// {
	// 	while (shell)
	// 	{
	// 		if (shell->next && pipe(fd) == -1)
	// 			error("pipe", errno);
	// 		id = fork();
	// 		if (id == -1)
	// 			error("fork", errno);
	// 		if (id == 0)
	// 			child(shell, env, fd);
	// 		else
	// 		{
	// 			parent(shell, fd);
	// 			shell = shell->next;
	// 		}
	// 	}
	// 	waitpid(id, NULL, 0);
	// }
}
