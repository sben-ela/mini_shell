#include "../mini_shell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

char **full_cmds(t_cmd *cmd)
{
	char	**cmds;
	int i;

	i = 0;
	cmds = malloc(sizeof(char *) * (cmd_size(cmd) + 1));
	while(cmd)
	{
		cmds[i] = cmd->cmd;
		cmd = cmd->next;
		i++;
	}
	cmds[i] = 0;
	return (cmds);
}

int	cmd_size(t_cmd *cmds)
{
	int size;

	size = 0;
	while(cmds)
	{
		size++;
		cmds = cmds->next;
	}
	return (size);
}

int check_edges(char *str)
{
	//if (!str[0])
	//{
	//	printf("send null to check edges\n");
	//	return (0);
	//}
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (2);
	else
		return (0);
}

void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	t_shell	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}