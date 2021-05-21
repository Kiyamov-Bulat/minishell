#include "minishell.h"

static char	*replace_field(char *field, t_cmd *cmd, int *pos, char **env)
{
	char		*tmp;
	char		*res;
	char		*sval;
	extern int	g_last_res;

	res = field;
	tmp = NULL;
	if ((sval = ft_itoa(g_last_res)) == NULL)
		return (NULL);
	while (tmp == NULL || !ft_strequal(res, tmp))
	{
		free(tmp);
		tmp = res;
		res = ft_strreplace(tmp, REPLACE_M, sval);
	}
	free(tmp);
	tmp = res;
	if (res)
	{
		res = repair_field(tmp, &cmd->args, pos, env);
		free(tmp);
	}
	free(sval);
	return (res);
}

static int	replace_dollar(t_cmd *cmd, char **env)
{
	int		i;
	int		k;
	char	*tmp;

	k = 0;
	if (cmd->command)
		if (!(cmd->command = replace_field(cmd->command, cmd, &k, env)))
			return (1);
	if (cmd->file_in)
		if (!(cmd->file_in = replace_field(cmd->file_in, cmd, &k, env)))
			return (1);
	if (cmd->file_out)
		if (!(cmd->file_out = replace_field(cmd->file_out, cmd, &k, env)))
			return (1);
	i = k;
	while (cmd->args[i])
	{
		if (!(tmp = replace_field(cmd->args[i], cmd, &k, env)))
			return (1);
		cmd->args[i] = tmp;
		i = k == i ? i + 1 : k + 1;
		k = i;
	}
	return (0);
}

int			prepare_cmd(t_cmd *cmd, char **env)
{
	int			err;
	char		*tmp;

	err = replace_dollar(cmd, env);
	if ((tmp = get_abs_path_command(cmd->command, env)))
	{
		free(cmd->args[0]);
		cmd->args[0] = tmp;
	}
	if (!tmp || err)
		handle_error(MALLOC_ERROR, cmd->command);
	return (err);
}

char		*ft_strreplace(char *dst, const char *old, const char *new)
{
	int		i;
	int		new_sz;
	int		old_sz;
	char	*res;

	if ((i = ft_indexof(dst, old, 0)) == -1)
		return (ft_strdup(dst));
	new_sz = ft_strlen(new);
	old_sz = ft_strlen(old);
	res = (char *)malloc(i + new_sz + ft_strlen(dst + i + old_sz) + 1);
	ft_strlcpy(res, dst, i + 1);
	ft_strcpy(res + i, (char *)new);
	ft_strcpy(res + i + new_sz, dst + i + old_sz);
	return (res);
}

char		**parse_path(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tmp = envp[i] + 5;
			return (ft_split(tmp, ':'));
		}
		++i;
	}
	return (NULL);
}
