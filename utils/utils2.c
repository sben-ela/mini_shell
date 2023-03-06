#include "../mini_shell.h"

void    freedouble(char **args)
{
    int    i;

    i = 0;
    while(args[i])
        free(args[i++]);
    free(args);
}

t_redire    *new_redir(char *content, int type)
{
    t_redire    *new;

    new = malloc(sizeof(t_redire));
    if (!new)
        return (0);
    if (type == 0)
        new->infile = content;
    if (type == 1)
        new->outfile = content;
    if (type == 4)
    {
        if (check_edges(content) == 1)
            new->quotes = 1;
        else if (check_edges(content) == 2)
            new->quotes = 2;
        else
            new->quotes = 0;
        if(new->quotes == 1)
            new->delimiter = ft_strtrim(content, "\"");
        else if(new->quotes == 2)
            new->delimiter = ft_strtrim(content, "\'");
        else
            new->delimiter = content;
    }
    if (type == 5)
        new->outfile = content;
    if (type != 3)
        new->type = type;
    new->next = 0;
    return (new);
}

t_shell	*ft_lstlast(t_shell *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

int	check(char const *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrimfree(char *s1, char *set)
{
	int		i;
	int		len;
	char	*mem;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i] && check(set, s1[i]))
		i++;
	while (s1[len] && check(set, s1[len]))
		len--;
	mem = ft_substr(s1, i, len - i + 1);
	free(s1);
	return (mem);
}