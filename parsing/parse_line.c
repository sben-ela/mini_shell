/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:19:14 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/10 14:26:36 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_content	*parseword(char *word, char **env)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (check_edges(word) == 1)
	{
		content->quotes = SINGLE_QUOTE;
		content->content = expand(word, env);
		content->content = handle_param(content->content, '\"');
	}
	else if (check_edges(word) == 2)
	{
		content->quotes = DOUBLE_QUOTE;
		content->content = expand(word, env);
		content->content = handle_param(content->content, '\'');
	}
	else
	{
		content->quotes = WITHOUT_QUOTE;
		content->content = expand(word, env);
		content->content = handle_param(content->content, '\'');
		content->content = handle_param(content->content, '\"');
	}
	free(word);
	return (content);
}

void	full_cmd(t_shell **new, t_content *content)
{
	char	**tmp;
	int		j;

	j = 0;
	if (content->quotes == WITHOUT_QUOTE)
	{
		tmp = ft_split(content->content, ' ');
		free(content->content);
		while (tmp[j])
			cmd_add_back(&(*new)->cmd, new_cmd(tmp[j++]));
		free(tmp);
	}
	else
		cmd_add_back(&(*new)->cmd, new_cmd(content->content));
}

void	ft_getnew(char **split, char **env, int i, t_shell **new)
{
	t_content	*content;

	while (split[i])
	{
		content = parseword(split[i], env);
		split[i] = content->content;
		if (!ft_strcmp(split[i], ">"))
			(free(split[i]), redi_add_back(&(*new)->redir,
			new_redir(parseword(split[++i], env), OUTFILE)));
		else if (!ft_strcmp(split[i], "<"))
			(free(split[i]), redi_add_back(&(*new)->redir,
			new_redir(parseword(split[++i], env), INFILE)));
		else if (!ft_strcmp(split[i], "<<"))
			(free(split[i]), redi_add_back(&(*new)->redir,
			new_redir(parseword(split[++i], env), DELIMITER)));
		else if (!ft_strcmp(split[i], ">>"))
			(free(split[i]), redi_add_back(&(*new)->redir,
			new_redir(parseword(split[++i], env), APPEND)));
		else
			full_cmd(new, content);
		free(content);
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
	if (!split)
		return (0);
	ft_getnew(split, env, 0, &new);
	if (!new->cmd)
		new->type = 0;
	else
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
			pipe = PIPE;
		new = ft_lstnew(args[i], i, env, pipe);
		ft_lstadd_back(&shell, new);
	}
	freedouble(args);
	return (shell);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}
