#include "mini_shell.h"

void	print_data(t_shell *shell)
{
	int i;

	while(shell)
	{
		i = 0;
		printf("index : %d      pipe : %d\n", shell->index, shell->pipe);
		while(shell->cmds[i])
			printf("%s\t", shell->cmds[i++]);
		printf("\n");
		while(shell->redir)
		{
			if (shell->redir->type == INFILE)
				printf("INFILE : %s\n", shell->redir->infile);
			if (shell->redir->type == OUTFILE)
				printf("OUTFILE : %s\n", shell->redir->outfile);
			if (shell->redir->type == APPEND)
				printf("APPEND : %s\n", shell->redir->outfile);
			if (shell->redir->type == DELIMITER)
				printf("DELIMITER : %s : %d\n", shell->redir->delimiter, shell->redir->quotes);
			shell->redir = shell->redir->next;
		}
		shell = shell->next;
	}
	// printf("STATUS : %d\n", status);
}

void	freedata(t_shell **data)
{
	t_cmd		*tmp1;
	t_shell		*tmp2;
	t_redire	*tmp3;

	while(*data)
	{
		while ((*data)->cmd)
		{
			free((*data)->cmd->cmd);
			tmp1 = (*data)->cmd;
			(*data)->cmd = (*data)->cmd->next;
			free(tmp1);
		}
		while((*data)->redir)
		{
			if ((*data)->redir->type == INFILE)
				free((*data)->redir->infile);
			else if ((*data)->redir->type == OUTFILE)
				free((*data)->redir->outfile);
			else if ((*data)->redir->type == DELIMITER)
				free((*data)->redir->delimiter);
			else if ((*data)->redir->type == APPEND)
				free((*data)->redir->outfile);
			tmp3= (*data)->redir;
			(*data)->redir = (*data)->redir->next;
			free(tmp3);
		}
		free((*data)->cmds);
		tmp2 = *data;
		(*data) = (*data)->next;
		free(tmp2);
	}
}

void	mini_shell(char **env)
{
	t_shell *shell;
	t_env	*ev;
	char	*read;
	char	*line;

	ev = create_env(env);
	while (1)
	{
		read = readline("\033[1;34m➜  Mini_shell ✗ \033[0m");
		if (!read)
		{
			printf("exit\n"),
			exit(0);
		}
		add_history(read);
		status = parse_syntax(read, 0);
		if (read[0] && !status)
		{
			line = parse_read(read);
			shell = parse_line(line, env);
			// print_data(shell);
			execute(shell, ev);
			freedata(&shell);
			free(line);
			free(read);
			// system("leaks mini_shell");
		}
		else if (read[0])
			(free(read), printf("syntax error\n"));
		else
			free(read);
	}
}

int main(int ac, char **av, char **env)
{
	(void)av;

	status = 0;
	if(ac != 1)
	{
		printf("invalid number of argument\n");
		return(0);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	mini_shell(env);
	return 0;
}