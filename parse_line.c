#include "minishell.h"

/*
** Parse cmd arguments until meets '\n', '<', '>' or '|'
**
** Returns the last char read back to stdin buffer (ft_ungetch())
**
** Uses "safe_realloc" function to control occupancy and dynamic realloc
**
** Returns: parsed NULL-terminated array_of_args or NULL (if ERROR or EOF)
*/

static char		**parse_args(char **env)
{
	int		i;
	int		c;
	char	**args;

	i = 0;
	if (!(args = (char **)malloc(sizeof(char *) * BUFFER_SIZE)))
		return (NULL);
	args[i] = ft_strdup("");
	while (args[i++] && !skip_spaces() \
			&& (c = ft_getch()) > 0 \
			&& !ft_strchr(SPEC_CHARS, c))
	{
		ft_ungetch();
		if ((args = safe_realloc(args, i, sizeof(*args))) == NULL)
			return (NULL);
		args[i] = parse_seq(env);
	}
	if (c < 1 || !args[i - 1] || !ft_strchr(SPEC_CHARS, c))
		free_dpointer((void ***)&args, i != 0 && !args[i - 1] ? i - 1 : i);
	else
	{
		args = normalize_arr(args, i, sizeof(*args));
		ft_ungetch();
	}
	return (args);
}

static int		skip_pipe_n_semicolon(void)
{
	int c;
	int err;

	err = skip_spaces();
	if ((c = ft_getch()) > 0 && c != '|' && c != ';')
		ft_ungetch();
	if (err || c < 1)
		return (-1);
	return (c == '|');
}

static int		parse_filename(t_cmd *cmd, int is_out, char **env)
{
	int		c;
	int		err;
	void	**t;
	char	**file;

	c = 1;
	if (is_out && (c = ft_getch()) > 0)
	{
		if (c == '>')
			cmd->fl_append = 1;
		else
			ft_ungetch();
		file = &cmd->file_in;
	}
	else
		file = &cmd->file_out;
	err = c < 1 || skip_spaces();
	err |= (*file = parse_seq(env)) == NULL;
	if ((t = (void **)parse_args(env)))
		free(*t);
	cmd->fl_pipe = skip_pipe_n_semicolon();
	err |= (cmd->fl_pipe == -1);
	err |= merge_dpointer((void ***)&cmd->args, t ? t + 1 : t);
	free(t);
	return (err);
}

/*
** Parse and create cmd (type of t_cmd)
**
** If the last char == '\n', returns it back to stdin buffer (ft_ungetch())
**
** Returns: parsed cmd or NULL (if ERROR or EOF)
*/

static t_cmd	*parse_cmd(char **env)
{
	int		c;
	int		err;
	t_cmd	*cmd;

	if (skip_spaces() || (cmd = newcmd()) == NULL)
		return (NULL);
	err = 0;
	if ((cmd->command = parse_seq(env)))
		if ((cmd->args = parse_args(env)))
			if ((c = ft_getch()) > 0)
			{
				if (c == '<' || c == '>')
					err = parse_filename(cmd, c == '>', env);
				else if (c == '\n')
					ft_ungetch();
				cmd->fl_pipe = cmd->fl_pipe || c == '|';
			}
	if (!cmd->command || !cmd->args || c < 1 || err)
	{
		delcmd(cmd);
		cmd = NULL;
	}
	return (cmd);
}

/*
** ---Main parsing function---
**
** Read from stdin and parse command_line until meets '\n'
**
** Uses the construction like "do while"
**
** Uses "safe_realloc" function to control occupancy and dynamic realloc
**
** Returns: parsed command lines or NULL (if ERROR or EOF)
*/

t_cmd			**parse_cmd_line(char **env)
{
	int		i;
	int		c;
	t_cmd	**res;

	i = 0;
	if ((res = (t_cmd **)malloc(sizeof(t_cmd *) * BUFFER_SIZE)) == NULL)
		return (NULL);
	res[i] = parse_cmd(env);
	while (res[i++] != NULL && (c = ft_getch()) > 0 && c != '\n')
	{
		ft_ungetch();
		if ((res = safe_realloc(res, i, sizeof(*res))) == NULL)
			return (NULL);
		res[i] = parse_cmd(env);
	}
	if (!res[i - 1] || c < 1)
		free_dpointer((void ***)&res, i != 0 && !res[i - 1] ? i - 1 : i);
	else
		res = (t_cmd **)normalize_arr(res, i, sizeof(*res));
	return (res);
}
