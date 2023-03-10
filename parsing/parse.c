/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:01:50 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/10 11:50:37 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int handle_pipes(char *line)
{
    char *str;

    if (count_char(line, '\"') == ft_strlen(line) || count_char(line, '\'') == ft_strlen(line))
        return (1);
    str = ft_strtrim(line, " ");
    if (!str)
        return (0);
    if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
	{
        free(str);
        return (1);
    }
    free(str);
    return (0);
}

int parse_redir(char *line, int i)
{
    while (line[i])
	{
        if (line[i] == '<')
		{
            i++;
            if (!line[i] || (line[i - 1] == ' ' && line[i] == '<') ||
                line[i] == '>' || (line[i] == '<' && !line[i + 1]) ||
                (line[i] == '<' && line[i + 1] == '<'))
                return (1);
        }
        if (line[i] == '>')
		{
            i++;
            if ((line[i - 1] == ' ' && line[i] == '>') || line[i] == '<' ||
                !line[i] || (line[i] == '>' && !line[i + 1]) ||
                (line[i] == '>' && line[i + 1] == '>'))
                return (1);
        }
        i++;
    }
    return (0);
}

int parse(char **split_line, char *line)
{
    char *string;
    int i;

    i = 0;
    string = malloc(1);
    while(split_line[i])
        string = ft_strjoinfree(string, split_line[i++]);
    if (parse_redir(string, 0))
	{
		freedouble(split_line);
        return (1);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if ((line[i] == '>' || line[i] == '<') && line[i - 1] == ' ')
			{
				freedouble(split_line);
				return (1);
			}
			i++;
		}
		i++;
	}
	freedouble(split_line);
    return (0);
}

int parse_syntax(char *line, char c)
{
    int i = 0;
    char    *trimmed_line;

    if (handle_pipes(line) || count_single_quotes(line) || count_double_quotes(line))
        return (1);
    trimmed_line = ft_strdup(line);
    if (!count_double_quotes(line))
        trimmed_line = ft_strtrimfree(trimmed_line, "\"");
    if (count_single_quotes(line))
        trimmed_line = ft_strtrimfree(trimmed_line, "\'");
    if (parse(ft_split(trimmed_line, ' '), trimmed_line))
    {
        free(trimmed_line);
        return (1);
    }
    while (trimmed_line[i])
	{
        if (trimmed_line[i] == '\'' || trimmed_line[i] == '\"')
		{
            c = trimmed_line[i];
            while (trimmed_line[i] && trimmed_line[i] != c)
                i++;
        }
        if (trimmed_line[i] == '|')
		{
            while (trimmed_line[++i] == ' ');
            if (!trimmed_line[i] || trimmed_line[i] == '|')
            {
                free(trimmed_line);
                return (1);
            }
        }
        i++;
    }
    free(trimmed_line);
    return (0);
}


// mochkil f matalan echo "tlol'tttg" "lol", khass tspliti first then check ga3 dakchi lakhr
/*
Here are the changes made to the code:

handle_pipes now correctly frees the str variable before returning if there is a pipe symbol at the beginning or end of the string.

parse_syntax now initializes i to zero, since it's a static variable and needs to be reset between calls. It also checks if there is an odd number of single or double quotes in the input string.

The count_single_quotes and count_double_quotes functions were removed, since they are not defined in the provided code and are not necessary for the parse_syntax function to work.

In parse_redir, the condition (line[i] == '>' && !line[i + 1]) was added to check for a trailing redirect symbol '>' with no argument.
count_char now initializes `
*/