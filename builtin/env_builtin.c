/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:44:55 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/03 14:58:30 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int env_builtin(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd[1])
	{
		while (env->env[i])
		{
			if (ft_strchr(env->env[i], '=') != -1)
				printf("%s\n", env->env[i]);
			i++;
		}
	}
	else
	{
		// status = EXIT_FAILURE;
		return (ft_perror("minishell: env: Too many arguments.", NULL));
	}
	return (1);
}

// int	main(int ac, char **av, char **env)
// {
// 	char **cmd = ft_split("env", ' ');
// 	env_builtin(cmd, env);
// }