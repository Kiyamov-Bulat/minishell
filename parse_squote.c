#include "minishell.h"

/*
** Reads from STDIN to the char \' or \n and stores it in a buf
**
** Args:
**			| buf: str pointer | i: the storing start index |
**
** c: char from stdin
** if c == 0 => EOF; if c == -1 => ERROR
**
** Returns: number_of_parsed_char or -1 (if EOF, ERROR or last c != \')
**
** NOTE: if BUFFER_SIZE == 5, i == 2:
**			str == [[x][x][\0][x][x]]
*/

int	parse_squote(char **buf, int i)
{
	int		c;
	int		start_index;

	start_index = i;
	while ((c = ft_getch()) != '\'' && c != '\n' && c > 0)
	{
		(*buf)[i++] = c;
		if ((*buf = safe_realloc(*buf, i, sizeof(**buf))) == NULL)
			return (-1);
	}
	if (c != '\'')
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	(*buf)[i] = '\0';
	return (i - start_index);
}
