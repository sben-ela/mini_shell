/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:50:56 by aybiouss          #+#    #+#             */
/*   Updated: 2023/01/03 09:50:56 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**get_paths(char **env, t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				error("Split function failed", 1);
			return (paths);
		}
		i++;
	}
	ft_putstr_fd("Pipex : Command not found: ", 2);
	ft_putstr_fd(data->argv[0], 2);
	ft_putstr_fd("\n", 2);
	exit(127);
	return (NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	execute(t_data *data, char *cmd, char **env)
{
	data->argv = ft_split(cmd, ' ');
	data->paths = get_paths(env, data);
	data->cmd = get_cmd(data->paths, data->argv[0]);
	if (!data->cmd)
	{
		free_paths(data->paths);
		ft_putstr_fd("Pipex : Command not found: ", 2);
		ft_putstr_fd(data->argv[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(data->cmd, data->argv, env) == -1)
		error(NULL, errno);
}
// "ls -l" | "wc -w"