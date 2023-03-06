#include "../mini_shell.h"

int	handleread(char *line, int i, char c)
{
	line[i++] = ' ';
	line[i++] = c;
	line[i++] = c;
	line[i++] = ' ';
	return (i);
}

int	handledel(char *line, int i, char c)
{
	line[i++] = ' ';
	line[i++] = c;
	line[i++] = ' ';
	return (i);
}

char *parse_read(char *read)
{
    char	*line;
    int		i;
	int		j;

	i = j = 0;
    line = malloc(ft_strlen(read) + 1 + (count_redirect(read) * 2));
	if (!line)
		return (0);
    while (read[j])
    {
        if (read[j] == '<' && read[j + 1] == '<')
		{
			i = handleread(line, i, '<');
			j += 2;
		}
		else if (read[j] == '>' && read[j + 1] == '>')
		{
			i = handleread(line, i, '>');
			j += 2;
		}
		else if (read[j] == '<')
			i = handledel(line, i, '<'),j++;
		else if (read[j] == '>')
			i = handledel(line, i, '>'),j++;
			line[i] = read[j];
		i++;
		j++;
    }
	line[i] = '\0';
	return (line);
}
