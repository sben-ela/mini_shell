#include "../mini_shell.h"

int getend(char *str)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            while (ft_isalnum(str[j]))
                j++;
            return(j - 1);
        }
        i++;
    }
    return(0);
}

char *find_value(char *var, char **env)
{
    char *value;
    char *str;
    int i;

    i = 0;
    str = ft_strjoin(var, "=");
    while(env[i])
    {
        value = ft_strnstr(env[i], str, ft_strlen(var) + 1);
        if(value)
        {
            free(str);
            return(value + ft_strlen(var) + 1);
        }
        i++;
    }
    free(str);
    return(ft_strdup("\n"));
}

char	*char_join(char *str, char c)
{
	char	*dst;
	int		i;

	i = 0;
	if (!str)
	    return(0);
	dst = malloc(ft_strlen(str) + 2);
	while (str[i])
	{
	    dst[i] = str[i];
	    i++;
	}
	dst[i++] = c;
	dst[i] = '\0';
    free(str);
	return(dst);
}

char    *get_value(char *str, char **env)
{
    char    *var;
    char    *string;
    char    *value;
    int p;

    p = 0;
    string = malloc(1);
    string[0] = 0;
    while (*str)
    {
        if (*str == '\"')
            p = 1;
        if (*str == '$')
        {
            var = ft_substr(str, 1, getend(str));
            if(!var[0])
                value = ft_strdup("$");
            else
                value = find_value(var, env);
            string = ft_strjoinfree(string, value);
            str += ft_strlen(var) + 1;
            free(var);
        }
        else if (*str == '\'' && p != 1)
        {
            str++;
            while (*str && *str != '\'')
            {
                string = char_join(string, *str);
                str++;
            }
            str++;
        }
        else
        {
            string = char_join(string, *str);
            str++;
        }
        if (p == 1 && *str == '\"')
            p = 0;
    }
    return (string);
}
