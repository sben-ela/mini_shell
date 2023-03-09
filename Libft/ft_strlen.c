/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:49:33 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/08 20:16:35 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
    {
        printf("Error: null pointer passed to ft_strlen\n");
        return (0);
    }
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
