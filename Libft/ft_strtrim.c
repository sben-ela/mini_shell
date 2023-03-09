/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:35:00 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/08 22:09:01 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*mem;

	if (!s1 || !set)
		return (0);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i] && check(set, s1[i]))
		i++;
	while (len > 0 && check(set, s1[len]))
		len--;
	mem = ft_substr(s1, i, len - i + 1);
	return (mem);
}
