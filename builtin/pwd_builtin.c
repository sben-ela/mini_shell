/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:07:54 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/19 11:07:54 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	pwd_builtin(char *cmd)
{
	char	cwd[256];
	char	*dir;

	(void)cmd;
	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		perror("minishell: pwd: ");
		//status = EXIT_FAILURE;
		return (-1);
	}
	printf("%s\n", dir);
	//status = EXIT_SUCCESS;
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*cmd;

// 	cmd = NULL;
// 	pwd_builtin(cmd);
// }