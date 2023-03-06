/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:31:12 by aybiouss          #+#    #+#             */
/*   Updated: 2023/01/03 09:31:12 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_next_line(char **buff)
{
	int		i;
	ssize_t	nobr;
	char	byte;
	char	*buffer;

	i = 0;
	nobr = 1;
	buffer = (char *)malloc(sizeof(char) * 10000);
	if (!buffer)
		return (-1);
	nobr = read(0, &byte, 1);
	while (nobr > 0 && byte != '\n' && byte != '\0')
	{
		if (byte != '\n' && byte != '\0')
			buffer[i] = byte;
		i++;
		nobr = read(0, &byte, 1);
	}
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*buff = buffer;
	return (1);
}

void	here_doc(t_data *data, char *limiter, char **av, char **env)
{
	char	*buff;

	if (pipe(data->fd) == -1)
		error("pipe", errno);
	while (write(1, "here_doc>", 9) && get_next_line(&buff))
	{
		if (!ft_strncmp(buff, limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(buff, data->fd[1]);
		free(buff);
	}
	free(buff);
	if (dup2(data->fd[0], 0) == -1)
		error("dup2", errno);
	free(limiter);
	close(data->fd[0]);
	close(data->fd[1]);
	while (data->i <= data->last)
	{
		processing(data, av, env);
		data->i++;
	}
	while (wait(NULL) != -1)
		;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac < 5)
		error("Run it like this: \"./pipex file1 cmd1 cmd2 ... cmdn file2\"", 1);
	if (!ft_strncmp(av[1], "here_doc", 9) && ac > 5)
	{
		parsing(&data, ac, av, 'h');
		here_doc(&data, ft_strjoin(av[2], "\n"), av, env);
	}
	else
	{
		parsing(&data, ac, av, 'p');
		pipex(&data, av, env);
	}
}
