/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:54:15 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/17 16:18:00 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	lengthstring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	lengthstring = ft_strlen(s);
	if (!s[start] || start >= lengthstring || len == 0)
		return (ft_strdup(""));
	if (len > (lengthstring - start))
		len = lengthstring - start;
	mem = malloc(len + 1);
	if (!mem)
		return (NULL);
	while (len > i && s[start] != '\0')
		mem[i++] = s[start++];
	mem[i] = '\0';
	return (mem);
}
