/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:38:23 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/22 15:38:23 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	del_env_elem(t_env *env, t_env_elem *elem)
{
	if (elem)
	{
    	if (elem == env->head)
       		env->head = elem->next;
    	if (elem->prev)
       		elem->prev->next = elem->next;
   		if (elem->next)
    		elem->next->prev = elem->prev;
    	free(elem->key);
    	free(elem->value);
    	free(elem);
    	env->size--;
    }
}

t_env_elem	*search_env_elem(t_env *env, char *key)
{
	t_env_elem	*tmp;

	tmp = env->head;
	while (tmp && strcmp(tmp->key, key))
		tmp = tmp->next;
	return (tmp);
}

void	print_env(t_env *env)
{
	t_env_elem	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	del_env(t_env *env)
{
	t_env_elem	*tmp;
	t_env_elem	*save;

	tmp = env->head;
	while (tmp)
	{
		save = tmp;
		free(tmp->key);
		free(tmp->value);
		tmp = tmp->next;
		free(save);
	}
	free(env);
}

char	**convert_array(t_env *env)
{
	t_env_elem	*tmp;
	char		**arr;
	int			i;

	i = 0;
	tmp = env->head;
	arr = malloc((env->size + 1) * sizeof(char *));
	if (!arr)
	{
		free(arr);
		return (NULL);
	}
	while (i < env->size)
	{
		arr[i] = ft_strdup(tmp->key);
		if (tmp->value)
		{
			arr[i] = ft_strjoinfree(arr[i], "=");
			arr[i] = ft_strjoinfree(arr[i], tmp->value);
		}
		tmp = tmp->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}
