/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:31:20 by aybiouss          #+#    #+#             */
/*   Updated: 2023/01/03 09:31:20 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	error(char *str, int n)
{
	if (str)
	{
		ft_putstr_fd("Pipex : ", 2);
		ft_putstr_fd(strerror(n), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(n);
}

void	parsing(t_data *data, int ac, char **av, char c)
{
	if (c == 'h')
	{
		data->i = 3;
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		data->infile = open(av[1], O_RDONLY);
		data->i = 2;
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	data->last = ac - 2;
}

void	child(t_data *data, char **av, char **env)
{
	if (data->i == data->last)
	{
		if (data->outfile == -1)
			error(av[data->i + 1], 13);
		if (dup2(data->outfile, 1) == -1)
			error("dup2", errno);
		close(data->outfile);
	}
	else
	{
		if (data->infile == -1 && data->i == 2)
			error(av[1], 2);
		if (dup2(data->fd[1], 1) == -1)
			error("dup2", errno);
		close(data->infile);
	}
	close(data->fd[0]);
	close(data->fd[1]);
	execute(data, av[data->i], env);
}

void	processing(t_data *data, char **av, char **env)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		error("pipe", errno);
	pid = fork();
	if (pid == -1 && data->i < data->last)
		error("fork", errno);
	if (pid == 0)
		child(data, av, env);
	else
	{
		if (dup2(data->fd[0], 0) == -1)
			error("dup2", errno);
		close(data->fd[0]);
		close(data->fd[1]);
	}
}

void	pipex(t_data *data, char **av, char **env)
{
	dup2(data->infile, 0);
	close(data->infile);
	while (data->i <= data->last)
	{
		processing(data, av, env);
		data->i++;
	}
	while (wait(NULL) != -1)
		;
}
