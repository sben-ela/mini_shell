/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/09 14:25:35 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	here_doc(t_redire *redir, char **env)
{
	int			fd;
	char		*str;
	// static int	i;

	// signal(SIGINT, sigint_handler);
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
		printf("%d\n", redir->quotes);
		if (!redir->quotes)
			str = expand_env(str, env);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	// unlink("tz");
	// close(fd);
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

void	is_directory(char *str, int n)
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

void	if_directory(char *str)
{
	if (!opendir(str))
		return ;
	ft_putstr_fd("Minishell", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	status = 126;
	exit(126);
}

void	ft_execute(t_shell *shell, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		exec_redir(shell);
		check_fd(shell->cmd);
		if_directory(shell->cmds[0]);
		if (check_builtins(shell->cmds[0]) == 1)
			ft_which_cmd(shell->cmds, env);
		else
			execute_cmd(shell, env->env);
	}
	if (shell->cmd->fd.in != 0)
		close(shell->cmd->fd.in);
	if (shell->cmd->fd.out != 1)
		close(shell->cmd->fd.out);
	waitpid(pid, &status, 0);
	// printf("%d\n", status);
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
	t_shell	*here;
	int	i;

	i = 0;
	tmp = shell;
	here = shell;
	while (tmp)
	{
		while (tmp->redir)
		{
			if (tmp->redir->type == DELIMITER)
				i++;
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
	if (i > 16)
	{
		error("too many heredocs", 2);//talmnb3d
		exit(2);
	}
	else
	{
		while (here)
		{
			while (here->redir)
			{
				if (here->redir->type == DELIMITER)
					here_doc(here->redir, env->env);
				here->redir = here->redir->next;
			}
			here = here->next;
		}
	}
}

//GT

int exec_redir_in(char *infile, int *in)
{
    if (access(infile, F_OK) == 0)
    {
        if (*in != STDIN_FILENO && *in > 0) // add error checking
        {
            if (close(*in) == -1) // add error checking
                error("close", errno);
        }
        if ((*in = open(infile, O_RDONLY, 0666)) == -1) // add error checking
            error("open", errno);
        return (1);
    }
    else
    {
        *in = -1;
        write(2, "minishell: \n", 12);
		printf("%s\n", infile);
        ft_perror(infile, ": No such file or directory");
        return (0);
    }
}

void check_fd(t_cmd *cmd)
{
    if (cmd->fd.in != STDIN_FILENO && cmd->fd.in > 0)
    {
        if (dup2(cmd->fd.in, STDIN_FILENO) == -1)
            error("dup2", errno);
        if (close(cmd->fd.in) == -1)
            error("close", errno);
    }
    if (cmd->fd.out != STDOUT_FILENO && cmd->fd.out > 1)
    {
        if (dup2(cmd->fd.out, STDOUT_FILENO) == -1)
            error("dup2", errno);
        if (close(cmd->fd.out) == -1)
            error("close", errno);
    }
}

void	exec_redir(t_shell *shell)
{
	t_redire	*redir;

	redir = shell->redir;
	if (!redir)
		return ;
	while (redir)
	{
		if (redir->type == INFILE)
			exec_redir_in(redir->infile, &shell->cmd->fd.in);
		if (redir->type == OUTFILE || redir->type == APPEND)
		{
			if (redir->type == OUTFILE)
				shell->cmd->fd.out = open(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (redir->type == APPEND)
				shell->cmd->fd.out = open(redir->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (shell->cmd->fd.out == -1)
				error("open", errno);
		}
		redir = redir->next;
	}
}

void	dup_close(t_fd *fd)
{
	if (fd->in != STDIN_FILENO && fd->in > 0)
    {
        if (dup2(fd->in, STDIN_FILENO) == -1)
            error("dup2", errno);
        if (close(fd->in) == -1)
            error("close", errno);
    }
    if (fd->out != STDOUT_FILENO && fd->out > 1)
    {
        if (dup2(fd->out, STDOUT_FILENO) == -1)
            error("dup2", errno);
        if (close(fd->out) == -1)
            error("close", errno);
    }
}

void	execute_cmd(t_shell *shell, char **env)
{
	char	**paths = NULL;
	char	*argv = NULL;

	paths = get_paths(env, shell);
	argv = get_cmd(paths, shell->cmds[0]);
	if (!argv)
	{
		status = 127;
		free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(ft_strtrim(shell->cmds[0], "\""), 2);
		ft_putstr_fd(": Command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(argv, shell->cmds, env) == -1)
		error(NULL, errno);
	// else
	// {
	// 	free(argv);
	// 	free_paths(paths);
	// }
}

void	child(t_shell *shell, t_env *env)
{
    exec_redir(shell);
    dup_close(&shell->cmd->fd);
    if (shell->next != NULL) 	// close the pipe ends
        close(shell->cmd->fd.out);
    if (check_builtins(shell->cmds[0]))
        ft_which_cmd(shell->cmds, env);
    else
        execute_cmd(shell, env->env);
	exit(EXIT_SUCCESS);
}

void	parent(t_shell *shell)
{
    if (shell->cmd->fd.in != STDIN_FILENO)
    	close(shell->cmd->fd.in);
    if (shell->cmd->fd.out != STDOUT_FILENO)
        close(shell->cmd->fd.out);
}

void	waitchilds(void)
{
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status));
   	// 	printf("Child process exited with status %d\n", WEXITSTATUS(status));
 	else if (WIFSIGNALED(status))
		status += 128;
 	// else if (WIFSTOPPED(status))
	// 	printf("Child process stopped due to signal %d\n", WSTOPSIG(status));
 	// else if (WIFCONTINUED(status))
   	// 	printf("Child process continued\n");
	// if (WIFEXITED(status))
    //     printf("Child process exited with status %d\n", WEXITSTATUS(status));
	// if (status > 256)
	// 	printf("status after %d\n", status / 256);
	// else
	// printf("status after %d\n", status);
}

void	execute(t_shell *shell, t_env *env)
{
	int		fd[2];
	pid_t	pid;

	while (shell && shell->next)
	{
		if (pipe(fd) == -1)
			error("pipe", errno);
		shell->cmd->fd.out = fd[1];
		shell->next->cmd->fd.in = fd[0];
		pid = fork();
		if (pid == -1)
			error("fork", errno);
		if (pid == 0)
		{
			close(fd[0]);
			child(shell, env);
		}
		else
		{
			parent(shell);
			close(fd[1]);
			shell = shell->next;
		}
	}
	if (shell)
		ft_execute(shell, env);
	waitchilds();
}