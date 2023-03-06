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
}

void	freedata(t_shell **data)
{
	t_shell *tmp;

	tmp = *data;
	while(*data)
	{
		while ((*data)->cmd)
		{
			free((*data)->cmd->cmd);
			free((*data)->cmd);
			(*data)->cmd = (*data)->cmd->next;
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
			free((*data)->redir);
			(*data)->redir = (*data)->redir->next;
		}
		free((*data)->cmds);
		free(*data);
		(*data) = (*data)->next;
	}
}

void	mini_shell(char **env)
{
	char *read;
	char *line;
	t_shell *shell;
	t_env	*ev;

	ev = create_env(env);
	while (1)
	{
		read = readline("\033[0;32mMinishell>> \033[0m");
		if (!read)
			exit(0);
		add_history(read);
		if (read[0] && !parse_syntax(read, 0))
		{
			line = parse_read(read);
			shell = parse_line(line, ev->env);
			print_data(shell);
			freedata(&shell);
			free(line);
			free(read);
			// system("leaks mini_shell");
			// execute(shell, ev);
		}
		else if (read[0])
			printf("syntax error\n");
	}
}

int main(int ac, char **av, char **env)
{
	(void)av;

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