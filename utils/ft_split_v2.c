/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:05:16 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/07 20:44:18 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	ft_lenword(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

static char	*ft_fullstr(char const *str, char c)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = ft_lenword(str, c);
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	**ft_second(char **strs, char const *str, char c, int count)
{
	int	i;
	int	len;

	i = 0;
	while (*str)
	{
		len = 0;
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strs[i] = ft_fullstr(str, c);
			if (!strs[i])
			{
				ft_free(strs, i);
				return (NULL);
			}
			i++;
		}
		len = ft_lenword(str, c);
		while (*str && len)
		{
			str++;
			len--;
		}
	}
	strs[count] = NULL;
	return (strs);
}

static int	ft_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			count++;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			char n = str[i++];
			while (str[i] && str[i] != n)
				i++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

char	**ft_split_v2(char const *str, char c)
{
	char	**strs;
	int		count;

	if (!str)
		return (NULL);
	count = ft_count(str, c);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	strs = ft_second(strs, str, c, count);
	return (strs);
}


//
//static int	ft_lenword(char const *str, char c)
//{
//    int i = 0;
//
//    while (str[i] && str[i] != c)
//    {
//        if (str[i] == '"')
//        {
//            i++;
//            while (str[i] && str[i] != '"')
//                i++;
//            if (str[i] == '"')
//                i++;
//        }
//        if (str[i] == '\'')
//        {
//            i++;
//            while (str[i] && str[i] != '\'')
//                i++;
//            if (str[i] == '\'')
//                i++;
//        }
//        if (str[i] && str[i] != c)
//            i++;
//    }
//    return (i);
//}
//
//static char	*ft_fullstr(char const *str, char c)
//{
//	char	*word;
//	int		i;
//	int		len;
//
//	i = 0;
//	len = ft_lenword(str, c);
//	word = malloc(len + 1);
//	if (!word)
//		return (NULL);
//	while (i < len)
//	{
//		word[i] = str[i];
//		i++;
//	}
//	word[i] = '\0';
//	return (word);
//}
//
//static void	ft_free(char **strs, int i)
//{
//	while (i >= 0)
//	{
//		free(strs[i]);
//		i--;
//	}
//	free(strs);
//}
//
//static char	**ft_second(char **strs, const char *str, char c, int count)
//{
//	int	i;
//	int len;
//
//	i = 0;
//	while (*str)
//	{
//		len = 0;
//		while (*str && *str == c)
//			str++;
//		if (*str)
//		{
//			strs[i] = ft_fullstr(str, c);
//			if (!strs[i])
//			{
//				ft_free(strs, i - 1);
//				return (NULL);
//			}
//			i++;
//		}
//		len = ft_lenword(str, c);
//		while (*str && len)
//		{
//			if (*str == '"' || *str == '\'')
//			{
//				char quote = *str++;
//				while (*str && *str != quote)
//					str++;
//			}
//			str++;
//			len--;
//		}
//	}
//	strs[count] = NULL;
//	return (strs);
//}
//
//char	**ft_split_v2(char const *str, char c)
//{
//	char	**strs;
//	int		count;
//
//	if (!str)
//		return (NULL);
//	count = ft_count(str, c);
//	strs = malloc(sizeof(char *) * (count + 1));
//	if (!strs)
//		return (NULL);
//	strs = ft_second(strs, str, c, count);
//	return (strs);
//}
