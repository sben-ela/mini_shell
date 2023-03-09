/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:29 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/08 19:44:42 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	unset_env(char *cmd, t_env *env)
{
	t_env_elem	*elem;

	elem = NULL;
	if (cmd && !ft_isalpha(cmd[0]))
	{
		printf("minishell: unset: `%s`: not a valid identifier\n",
			cmd);
		status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	else
	{
		elem = search_env_elem(env, cmd);
		if (elem)
			del_env_elem(env, elem);
	}
}

int	unset_builtin(char **cmd, t_env *env)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		unset_env(cmd[i], env);
		free(cmd[i]);
		i++;
	}
	env->env = convert_array(env);
	status = EXIT_SUCCESS;
	return (status); //status hnayya succesfully
}
//status needed !

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char **read;
// 	int	i;
	
// 	read = ft_split("unset ebbeb", ' ');
// 	unset_builtin(read, &env);
// 	i = 0;
// 	while (env[i])
// 		printf("%s\n", env[i++]);
// 	system("leaks a.out");
// }