#include "minishell.h"

/*
** args:
**		buf: pointer of result-str,
**		c: read char,
**		i: current index of buf,
**		env: env variables
**
** returns: number of parsed characters
*/

static int	parse_dquote_base(char **buf, int c, int i, char **env)
{
	int n;

	if (c == '\\')
		n = parse_escaped_seq(buf, i, 0);
	else if (c == '$')
		n = parse_dollar_seq(buf, i, env, ENV_MDQ);
	else
	{
		(*buf)[i] = c;
		n = 1;
	}
	return (n);
}

/*
** Reads from STDIN to the char \" or \n and stores it in a buf
**
** Args:
**		| buf: str pointer | i: the storing start index | env: env vars |
**
** c: char from stdin
** if c == 0 => EOF; if c == -1 => ERROR
**
** Also parses dollar seq and escaped seq
**
** Returns: number_of_parsed_char or -1 (if EOF, ERROR or last c != \")
**
** NOTE: if BUFFER_SIZE == 5, i == 2:
**		str == [[x][x][\0][x][x]]
*/

int			parse_dquote(char **buf, int i, char **env)
{
	int		c;
	int		n;
	int		start_index;

	start_index = i;
	while ((c = ft_getch()) != '\"' && c != '\n' && c > 0)
	{
		if ((n = parse_dquote_base(buf, c, i, env)) == -1)
			return (-1);
		i += n;
		if ((*buf = safe_realloc(*buf, i, sizeof(**buf))) == NULL)
			return (-1);
	}
	if (c != '\"')
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	(*buf)[i] = '\0';
	return (i - start_index);
}
