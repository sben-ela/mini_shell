/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:46:45 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/25 07:37:25 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*save;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		save = temp;
		del(temp->content);
		temp = temp->next;
		free(save);
	}
	*lst = NULL;
}
