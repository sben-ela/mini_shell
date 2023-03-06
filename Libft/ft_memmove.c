/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:36:47 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/25 17:34:28 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	unsigned char	*dest;
	unsigned char	*sorc;
	size_t			i;

	i = 0;
	dest = (unsigned char *) dst;
	sorc = (unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (sorc > dest)
		ft_memcpy(dest, sorc, length);
	else
	{
		while (length > i)
		{
			dest[length - i - 1] = sorc[length - i - 1];
			i++;
		}
	}
	return (dest);
}
