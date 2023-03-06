#include "../mini_shell.h"

int	ft_perror(char *msg, char *utils)
{
	write(2, msg, ft_strlen(msg));
	if (utils)
		write(2, utils, ft_strlen(utils));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	ft_puterr(char *cmd, char *arg, char *msg, int errnum)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	if (!msg)
		perror("");
	else
		printf("%s\n", msg);
	// status = errnum;
	return (errnum);
    // return (1); // for the moment
}
