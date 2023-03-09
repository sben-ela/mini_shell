/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:26 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/08 20:39:41 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*new_cmd(char *content)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if(!new)
		return (0);
	new->cmd = content;
	new->fd.in = 0;
	new->fd.out = 1;
	new->next = 0;
	return (new);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (*lst == 0)
		*lst = new;
	else
	{
		tmp = last_cmd(*lst);
		tmp->next = new;
	}
}

t_redire	*redilast(t_redire *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	redi_add_back(t_redire **lst, t_redire *new)
{
	t_redire	*tmp;

	if (*lst == 0)
		*lst = new;
	else
	{
		tmp = redilast(*lst);
		tmp->next = new;
	}
}
