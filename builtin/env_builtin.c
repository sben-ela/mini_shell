/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:44:55 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/08 19:44:42 by aybiouss         ###   ########.fr       */
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
		status = EXIT_SUCCESS;
	}
	else
	{
		status = EXIT_FAILURE;
		ft_putstr_fd("Minishell: env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	return (status);
}

// int	main(int ac, char **av, char **env)
// {
// 	char **cmd = ft_split("env", ' ');
// 	env_builtin(cmd, env);
// }