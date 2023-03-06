/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:31:48 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/25 11:11:34 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(void *buffer, int ch, size_t length)
{
	unsigned char	*buf;
	size_t			i;

	i = 0;
	buf = (unsigned char *)buffer;
	while (i < length)
	{
		if (buf[i] == (unsigned char) ch)
			return (buf + i);
		i++;
	}
	return (NULL);
}
