/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:49:33 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/05 13:02:58 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
    {
        printf("Error: null pointer passed to ft_strlen\n");
        exit(EXIT_FAILURE);
    }
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
