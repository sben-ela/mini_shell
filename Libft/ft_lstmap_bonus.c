/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:20:21 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/26 16:58:38 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	temp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&temp, del);
			return (NULL);
		}
		ft_lstadd_back(&temp, new);
		new = new->next;
		lst = lst->next;
	}
	return (temp);
}

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*temp;
// 	t_list	*save;

// 	if (!lst || !del)
// 		return ;
// 	temp = *lst;
// 	while (temp)
// 	{
// 		save = temp;
// 		del(temp->content);
// 		temp = temp->next;
// 		free(save);
// 	}
// 	*lst = NULL;
// }

// void	*f(void *content)
// {
// 	char *str;
// 	int	i;

// 	i = 0;
// 	str = (char *)content;
// 	while (str[i])
// 	{
// 		str[i] -= 32;
// 		i++;
// 	}
// 	return ((void *)str);
// }

// void	del(void *content)
// {
// 	free(content);
// }

// int	main()
// {
// 	t_list	*d;
// 	t_list	*node = ft_lstnew(strdup("salam"));
// 	int	i;

// 	i = 0;
// 	while (i < 20)
// 	{
// 		ft_lstadd_back(&node, ft_lstnew(strdup("hillo")));
// 		i++;
// 	}
// 	d = ft_lstmap(node, f, del);
// 	while (d)
// 	{
// 		printf("%s\n", d->content);
// 		d = d->next;
// 	}
// }
