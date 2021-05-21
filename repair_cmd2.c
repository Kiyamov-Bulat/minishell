#include "minishell.h"

int		is_join(char *tail, char *env_val, int last_res)
{
	static int res = 0;

	if (last_res)
		return (res);
	res = !*tail || (env_val && !ft_isspace(*env_val));
	return (res);
}

int		free_tmp_splt(char ***splt, int free_zero)
{
	if (free_zero)
	{
		free((*splt)[0]);
		(*splt)[0] = NULL;
	}
	free(*splt);
	*splt = NULL;
	return (0);
}

int		insert_new_args(char **new, char ***args_buf, int *pos,\
		int from_zero)
{
	if (new[0] != NULL && (new[1] != NULL || from_zero))
	{
		*pos = ft_insert(args_buf, new + !from_zero, *pos + 1) - 1;
		return (1);
	}
	return (0);
}
