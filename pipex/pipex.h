/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:30:52 by aybiouss          #+#    #+#             */
/*   Updated: 2023/01/03 09:30:52 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>

typedef struct s_data {
	int		infile;
	int		outfile;
	int		i;
	int		last;
	int		fd[2];
	char	**paths;
	char	**argv;
	char	*cmd;
}	t_data;

//utils
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);

//error
void	error(char *str, int n);

void	parsing(t_data *data, int ac, char **av, char c);
void	pipex(t_data *data, char **av, char **env);
void	processing(t_data *data, char **av, char **env);
void	child(t_data *data, char **av, char **env);
void	execute(t_data *data, char *cmd, char **env);
char	**get_paths(char **env, t_data *data);
char	*get_cmd(char **paths, char *cmd);
void	free_paths(char **paths);
void	here_doc(t_data *data, char *limiter, char **av, char **env);
int		get_next_line(char **buff);

#endif