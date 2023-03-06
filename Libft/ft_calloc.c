/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:20:58 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/02 10:24:21 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitmes, size_t size)
{
	void	*res;

	if (size && (SSIZE_MAX / size) < nitmes)
		return (NULL);
	res = malloc(nitmes * size);
	if (!res)
		return (NULL);
	ft_bzero(res, nitmes * size);
	return (res);
}
