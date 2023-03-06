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

int	*skip_char_between_quotes(char *line, char *new_line, int i, int j)
{
	int *tab = malloc(8);
	if(line[i] == '"')
	{
		new_line[j++] = line[i++];
			while(line[i] && line[i] != '"')
				new_line[j++] = line[i++];
		new_line[j++] = line[i++];
	//printf("IN FUNCTION i:%d j:%d\n", i, j);
	}
	if(line[i] == '\'')
	{
		new_line[j++] = line[i++];
			while(line[i] && line[i] != '\'')
				new_line[j++] = line[i++];
		new_line[j++] = line[i++];
	}
	//printf("%s\n", new_line[0]);
	tab[0] = i;
	tab[1] = j;
	return (tab);
}

int *skip_del(char *line, char *new_line, int i, int j, char c)
{
	int *tab;

	tab = malloc(8);
	new_line[j++] = '|';
	new_line[j++] = c;
	new_line[j++] = c;
	new_line[j++] = '|';
	// skipp "<<"
	i += 2;
	// cpy the the string after <<
	if(line[i] && line[i] != '|')
	{
		new_line[j++] = '|';
		while(line[i] == ' ')
			i++;
		while(line[i] && line[i] != '|' && line[i] != ' ')
			new_line[j++] = line[i++];
		new_line[j++] = '|';
	}
	tab[0] = i;
	tab[1] = j;
	return (tab);
}

void	parse_all(char *line, char *new_line, int i, int j)
{
	int *tab;

	while (line[i])
	{
		tab = skip_char_between_quotes(line, new_line, i, j);
		i = tab[0];
		j = tab[1];
		//free(tab);
		//if we have "<<" in this case we make the the dilimeter between to pipe like it "|<<|"
		if(line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<')
		{
			tab = skip_del(line, new_line, i, j, '<');
			i += tab[0];
			j += tab[1];
			//free(tab);
		}
		else if(line[i] == '>' && line[i + 1] == '>' && line[i + 2] != '>')
		{
			tab = skip_del(line, new_line, i, j, '>');
			i += tab[0];
			j += tab[1];
			//free(tab);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			new_line[j++] = '|';
			new_line[j++] = line[i++];
			new_line[j++] = '|';
			// cpy the the string after > or <
			if(line[i] && line[i] != '|')
			{
				new_line[j++] = '|';
				while(line[i] == ' ')
					i++;
				while(line[i] && line[i] != '|' && line[i] != ' ' && line[i] != '>' && line[i] != '<')
					new_line[j++] = line[i++];
				while(line[i] && line[i] == ' ')
					i++;
				new_line[j++] = '|';
			}
		}
		// cpy character in the new string
		if(line[i] != '>' && line[i] != '<')
			new_line[j++] = line[i++];
	}
	// add null in the last of the new string
	new_line[j] = '\0';
}

char	*parse_redirect(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	j = i = 0;
	/// allocate to the new string
	new_line = malloc(ft_strlen(line) + 1 + (count_redirect(line) * 2));
	if (!new_line)
		return (0);
	parse_all(line, new_line, i, j);
	//printf("%s\n", new_line);
	return(new_line);
}

