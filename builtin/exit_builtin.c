/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/03 16:24:54 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int exit_builtin(char **cmd, t_env *env)
{
    (void)cmd;    //only need to free all parsing and execution part
    (void)env;
    exit(1);
}