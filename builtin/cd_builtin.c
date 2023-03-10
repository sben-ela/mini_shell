/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:13:14 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/10 10:50:15 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

// ~ cd 
// depends on ch7sl mn n9ta anrj3o lour

void	set_dir(t_env *ev, char *cwd, char *owd)
{
	t_env_elem	*env_elem;

	env_elem = search_env_elem(ev, "PWD");
	if (!env_elem)
		return ;
	env_elem->value = ft_strdup(cwd);
	env_elem = search_env_elem(ev, "OLDPWD");
	if (!env_elem)
		return ;
	env_elem->value = ft_strdup(owd);
}

int	cd_builtin(char **cmd, t_env *env)
{
	char		cwd[524];
	char		owd[524];

	getcwd(owd, sizeof(owd));
	if (!cmd[1])
	{
		if (chdir(expand_env("$HOME", env->env)) != 0)
			return (ft_puterr(cmd[0],
					expand_env("$HOME", env->env), NULL, 1));
	}
	else
	{
		if (!ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--"))
		{
			if (chdir(expand_env("$HOME", env->env)) != 0)
				return (ft_puterr(cmd[0],
						expand_env("$HOME", env->env), NULL, 1));
		}
		else if (!ft_strcmp(cmd[1], "-"))
		{
			if (chdir(expand_env("$OLDPWD", env->env)) != 0)
				return (ft_puterr(cmd[0],
						expand_env("$OLDPWD", env->env), NULL, 1));
		}
		else if (chdir(cmd[1]) != 0)
			return (ft_puterr(cmd[0], cmd[1], NULL, 1));
	}
	getcwd(cwd, sizeof(cwd));
	set_dir(env, cwd, owd);
	status = EXIT_SUCCESS;
	env->env = convert_array(env);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char	cmds[256];
// 	char	**cmd;

// 	cmd = ft_split("cd ../..", ' ');
// 	cd_builtin(cmd, &env);
// }
