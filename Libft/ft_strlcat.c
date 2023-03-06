/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:06:55 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/25 15:16:08 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t length)
{
	size_t	i;
	size_t	dl;
	size_t	sl;
	size_t	j;

	i = 0;
	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	j = dl;
	if (length == 0 || dl >= length)
		return (length + sl);
	while ((length - dl - 1) > i && src[i] != '\0')
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (sl + dl);
}
