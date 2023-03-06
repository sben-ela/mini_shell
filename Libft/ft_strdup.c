/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:29:57 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/24 15:06:13 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	char	*mem;
	int		i;

	i = 0;
	mem = malloc((ft_strlen(source) + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	while (source[i] != '\0')
	{
		mem[i] = source[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
