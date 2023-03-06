#include "../mini_shell.h"

char	*parseword(char *word, char **env)
{
	char	*new_word;

	if (check_edges(word) == 1)
	{
		new_word = get_value(word, env);
		new_word = handle_param(new_word, '\"');
	}
	else if (check_edges(word) == 2)
	{
		new_word = get_value(word, env);
		new_word = handle_param(new_word, '\'');
	}
	else
	{
		new_word = get_value(word, env);
		new_word = handle_param(new_word, '\'');
		new_word = handle_param(new_word, '\"');
	}
	free(word);
	return (new_word);
}

void	ft_getnew(char **split, char **env, int i, t_shell **new)
{
	char	**tmp;
	int		j;

	while (split[i])
	{
		split[i] = parseword(split[i], env);
		if (!ft_strcmp(split[i], ">"))
			(free(split[i]), redi_add_back(&(*new)->redir, new_redir(parseword(split[++i], env), OUTFILE)));
		else if (!ft_strcmp(split[i], "<"))
			(free(split[i]), redi_add_back(&(*new)->redir, new_redir(parseword(split[++i], env), INFILE)));
		else if (!ft_strcmp(split[i], "<<"))
			(free(split[i]), redi_add_back(&(*new)->redir, new_redir(parseword(split[++i], env), DELIMITER)));
		else if (!ft_strcmp(split[i], ">>"))
			(free(split[i]), redi_add_back(&(*new)->redir, new_redir(parseword(split[++i], env), APPEND)));
		else
		{
			if (check_edges(split[i]))
			{
				tmp = ft_split(split[i], ' ');
				j = 0;
				while (tmp[j])
					cmd_add_back(&(*new)->cmd, new_cmd(tmp[j++]));
			}
			else
				cmd_add_back(&(*new)->cmd, new_cmd(split[i]));
		}
		i++;
	}
}

t_shell	*ft_lstnew(char *content, int index, char **env, int pipe)
{
	t_shell	*new;
	char	**split;

	new = malloc(sizeof(t_shell));
	if (!new)
		return (0);
	new->cmd = 0;
	new->redir = 0; 
	split = ft_split_v2(content, ' ');
	if(!split)
		return (0);
	ft_getnew(split, env, 0, &new);
	new->type = 3;
	new->pipe = pipe;
	new->index = index;
	new->next = 0;
	new->cmds = full_cmds(new->cmd);
	free(split);
	return (new);
}

t_shell	*parse_line(char *line, char **env)
{
	char    **args;
	t_shell *shell;
	t_shell *new;
	int	    pipe;
	int	    i;
	(void)env;
	(void)line;
	(void)pipe;
	(void)new;
	i = -1;
	shell = 0;
	args = ft_split_v2(line, '|');
	if (!args)
		return (0);
	while (args[++i])
		args[i] = ft_strtrimfree(args[i], " ");
	i = -1;
	while (args[++i])
	{
		pipe = 0;
		if(args[i + 1])
			pipe = 1;   
		new = ft_lstnew(args[i], i, env, pipe);
		ft_lstadd_back(&shell, new);
	}
	freedouble(args);
	return (shell);
}

void	sigint_handler(int sig)
{
	if(sig == SIGINT)
	{
		write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 1);
		rl_redisplay();
	}
	else if(sig == SIGQUIT)
			return ;
}
