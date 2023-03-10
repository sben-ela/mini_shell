/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:19:18 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/09 17:22:15 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int getend(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (ft_isalnum(str[j]))
				j++;
			return (j - 1);
		}
		i++;
	}
	return(0);
}

char	*find_value(char *var, char **env)
{
	char	*value;
	char	*str;
	int		i;
 	
	i = 0;
	str = ft_strjoin(var, "=");
	while (env[i])
	{
		value = ft_strnstr(env[i], str, ft_strlen(var) + 1);
		if (value)
		{
			free(str);
			return(value + ft_strlen(var) + 1);
		}
		i++;
	}
	free(str);
	return (ft_strdup("\n"));
}

char	*char_join(char *str, char c)
{
	char	*dst;
	int		i;	

	i = 0;
	if (!str)
	    return(0);
	dst = malloc(ft_strlen(str) + 2);
	while (str[i])
	{
	    dst[i] = str[i];
	    i++;
	}
	dst[i++] = c;
	dst[i] = '\0';
	free(str);
	return (dst);
}

char    *get_value(char **str, char **string, char **env)
{
	char    *value;
	char    *var;

	if (*((*str) + 1) == '?')
	    value = ft_itoa(status/256), (*str)++, (*str)++;
	else
	{
		var = ft_substr(*str, 1, getend(*str));
		if (!var[0])
		    value = ft_strdup("$");
		else
		    value = find_value(var, env);
		*str += ft_strlen(var) + 1;
		free(var);
	}
	*string = ft_strjoinfree(*string, value);
	if (!ft_strcmp(value, "\n") || !ft_strcmp(value, "$"))
	    free(value);
	return (value);
}

char	*expand(char *str, char **env)
{
	char	*string;
	char	*value;
	int 	quote;

	quote = 0;
	string = malloc(1);
	string[0] = 0;
	while (*str)
	{
		if (*str == '\"')
			quote = DOUBLE_QUOTE;
		if (*str == '$')
			value = get_value(&str, &string, env);
		else if (*str == '\'' && quote != DOUBLE_QUOTE)
		{
			str++;
			while (*str && *str != '\'')
				(string = char_join(string, *str), str++);
			str++;
		}
		else
			(string = char_join(string, *str), str++);
		if (quote == DOUBLE_QUOTE && *str == '\"')
			quote = 0;
	}
	return (string);
}