#include "minishell.h"

int				parse_escaped_seq(char **buf, int index, int esc_all)
{
	int c;

	if ((c = ft_getch()) < 1 || c == '\n')
		return (-1);
	if (c == '$' || c == '\"' || c == '\\' || esc_all)
	{
		(*buf)[index] = c;
		return (1);
	}
	else
	{
		(*buf)[index] = '\\';
		if ((*buf = safe_realloc(*buf, index, sizeof(**buf))) == NULL)
			return (-1);
		(*buf)[index + 1] = c;
		return (2);
	}
}

int				parse_dollar_seq(char **buf, int index, \
		char **env, char marker)
{
	int		i;
	char	*dollar;

	i = 0;
	if ((dollar = parse_dollar(env, marker)) == NULL)
		return (0);
	while (dollar[i])
	{
		(*buf)[index + i] = dollar[i];
		i++;
		if ((*buf = safe_realloc(*buf, index + i, sizeof(**buf))) == NULL)
			return (-1);
	}
	free(dollar);
	return (i);
}

int				skip_spaces(void)
{
	int c;

	while (ft_isspace((c = ft_getch())) && c > 0 && c != '\n')
		;
	ft_ungetch();
	return (c < 1);
}

/*
** Args:
**		buf: pointer of result-str,
**		c: read char,
**		i: current index of buf,
**		env: env variables
**
** Returns: number of parsed characters
*/

static int		parse_seq_base(char **buf, int c, int i, char **env)
{
	int n;

	if (c == '\\')
		n = parse_escaped_seq(buf, i, 1);
	else if (c == '$')
		n = parse_dollar_seq(buf, i, env, ENV_MWQ);
	else if (c == '\'')
		n = parse_squote(buf, i);
	else if (c == '\"')
		n = parse_dquote(buf, i, env);
	else
	{
		(*buf)[i] = c;
		n = 1;
	}
	return (n);
}

/*
** Parse sequences like | Thisstr$HOME\""ABCD$PATH"'HElloWorld\t' |
**		until meets SPACE_CHARACTER (' ', '\t', '\n'...)
**
** Returns the last char read back to stdin buffer (ft_ungetch())
**
** Uses "safe_realloc" function to control occupancy and dynamic realloc
**
** Returns: parsed string or NULL (if ERROR or EOF)
*/

char			*parse_seq(char **env)
{
	int		i;
	int		n;
	int		c;
	char	*seq;

	i = 0;
	n = 0;
	seq = (char *)malloc(BUFFER_SIZE);
	while (seq && (c = ft_getch()) > 0 \
			&& !ft_isspace(c) && !ft_strchr(SPEC_CHARS, c))
	{
		if ((n = parse_seq_base(&seq, c, i, env)) == -1)
			break ;
		i += n;
		seq = safe_realloc(seq, i, sizeof(*seq));
	}
	if (c < 1 || n == -1 || seq == NULL)
	{
		if (seq)
			free(seq);
		return (NULL);
	}
	if ((seq = normalize_arr(seq, i, sizeof(*seq))) != NULL)
		ft_ungetch();
	return (seq);
}
