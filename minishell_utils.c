#include "minishell.h"

int		get_size(char **buf)
{
	int size;

	size = 0;
	while (*buf++)
		size++;
	return (size);
}

int		get_old_size(int i)
{
	return (i + BUFFER_SIZE - i % BUFFER_SIZE);
}

/*
**	Returns env variable
*/

char	*get_env_var(char *name, char **env)
{
	size_t	len;
	char	*eqsign;

	len = ft_strlen(name);
	while (*env)
	{
		eqsign = ft_strchr(*env, '=');
		if ((size_t)(eqsign - *env) == len)
			if (ft_strnstr(*env, name, len))
				return (eqsign + 1);
		env++;
	}
	return (NULL);
}

int		increase_shlvl(char *shlvl_val, char ***env)
{
	char	*shlvl_var[2];
	int		err;

	shlvl_val = shlvl_val ? shlvl_val : "";
	if ((shlvl_val = ft_itoa(ft_atoi(shlvl_val) + 1)) == NULL)
		return (-1);
	shlvl_var[0] = ft_strjoin("SHLVL=", shlvl_val);
	shlvl_var[1] = NULL;
	free(shlvl_val);
	if (shlvl_var[0] == NULL)
		return (-1);
	err = ft_export(shlvl_var, env);
	free(shlvl_var[0]);
	return (err);
}

int		merge_dpointer(void ***dst, void **p)
{
	int		i;

	i = 0;
	if (*dst == NULL || p == NULL)
		return (-1);
	while ((*dst)[i] != NULL)
		i++;
	while (*p != NULL && *dst != NULL)
	{
		(*dst)[i++] = *p++;
		*dst = safe_realloc(*dst, i, sizeof(**dst));
	}
	*dst = normalize_arr(*dst, i, sizeof(**dst));
	return (*dst == NULL);
}
