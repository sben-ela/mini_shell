/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:30:58 by aybiouss          #+#    #+#             */
/*   Updated: 2023/01/03 09:30:58 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		error("Run it like this: \"./pipex infile cmd1 cmd2 outfile\"", 1);
	parsing(&data, ac, av, 'p');
	pipex(&data, av, env);
}
