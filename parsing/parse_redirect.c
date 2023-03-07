#include "../mini_shell.h"

int plussize(char *str)
{
	int i;
	int count;

	i = count = 0;
	while(str[i] == ' ')
		i++;
	while(str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != ' ')
		i++;
	if(str[i] == ' ')
		return (1);
	return (0);
}

int count_redirect(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while(line[i])
	{
		if((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
		{
			if(plussize(line + i + 1))
				count++;
			count++;
		}
		else if(line[i] == '>' || line[i] == '<')
		{
			if(plussize(line + i + 1))
				count++;
			count++;
		}
		i++;
	}
	return(count);
}