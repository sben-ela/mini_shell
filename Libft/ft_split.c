/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:15:23 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/26 17:02:15 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**freeing(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (NULL);
}

static int	count_w(const char *s, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] == c)
		i++;
	while (s[len] == c)
		len--;
	if (len > i)
		j++;
	while (len > i)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			j++;
		i++;
	}
	return (j);
}

static char	*stdup(const char *s, int start, int fin)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(fin - start + 1);
	if (!str)
		return (NULL);
	while (fin > start)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static char	**addup(char **str, char const *s, char c, int count)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] != c && j < 0)
			j = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && j >= 0)
		{
			str[count++] = stdup(s, j, i);
			if (!str[count - 1])
				return (freeing(str));
			j = -1;
		}
		i++;
	}
	str[count] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	count = 0;
	if (!s)
		return (NULL);
	str = malloc((count_w(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = addup(str, s, c, count);
	return (str);
}
