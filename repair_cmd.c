#include "minishell.h"

static char		**split_env(char *env_val, char marker)
{
	char **res;

	if (env_val == NULL)
	{
		if ((res = (char **)malloc(sizeof(char *))) == NULL)
			return (NULL);
		res[0] = NULL;
	}
	else if (marker == ENV_MWQ)
	{
		if ((res = ft_split(env_val, ' ')) == NULL)
			return (NULL);
	}
	else
	{
		if ((res = (char **)malloc(sizeof(char *) * 2)) == NULL)
			return (NULL);
		res[0] = ft_strdup(env_val);
		res[1] = NULL;
	}
	return (res);
}

static void		add_end(char **s, char c)
{
	int		sz;
	char	*new;

	sz = ft_strlen(*s);
	if ((new = (char *)malloc(sz + 2)) == NULL)
		return ;
	ft_strcpy(new, *s);
	new[sz] = c;
	new[sz + 1] = '\0';
	free(*s);
	*s = new;
}

static char		*get_env(char *f, int start, char **env)
{
	int		end;
	char	t;
	char	smarker[2];
	char	*env_val;

	smarker[0] = f[start];
	smarker[1] = '\0';
	end = ft_indexof(f + start, smarker, 1) + start;
	t = f[end];
	f[end] = 0;
	env_val = get_env_var(f + start + 1, env);
	f[end] = t;
	return (env_val);
}

static char		*join_tail(char **tail, char *new_tail, char c, int is_join)
{
	char *tmp;

	if (c == ENV_MDQ || is_join)
	{
		tmp = *tail;
		if ((*tail = ft_strjoin(tmp, new_tail)) == NULL)
			return (NULL);
		free(tmp);
	}
	return (*tail);
}

char			*repair_field(char *f, char ***args, int *pos, char **env)
{
	int		i;
	char	*head;
	char	*enval;
	char	**tail;
	char	**pars;

	i = 0;
	head = (char *)ft_calloc(1, sizeof(char));
	tail = &head;
	while (f[i] && head)
		if (f[i] == ENV_MWQ || f[i] == ENV_MDQ)
		{
			enval = get_env(f, i, env);
			if (!(pars = split_env(enval, f[i])) || (pars[0] \
			&& !join_tail(tail, pars[0], f[i], is_join(*tail, enval, 0))))
				return (NULL);
			if (f[i] == ENV_MWQ \
			&& insert_new_args(pars, args, pos, !is_join(*tail, enval, 1)))
				tail = (*args) + (*pos);
			free_tmp_splt(&pars, is_join(*tail, enval, 1));
			i = ft_strchr(f + i + 1, f[i]) - f + 1;
		}
		else
			add_end(tail, f[i++]);
	return (head);
}
