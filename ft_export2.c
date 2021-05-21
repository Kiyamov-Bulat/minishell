#include "minishell.h"

static char	*put_in_quotes(char *str)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin("\"", str);
	tmp = result;
	result = ft_strjoin(result, "\"");
	free(tmp);
	return (result);
}

int			put_var_with_quotes(char *var)
{
	char	*tmp;
	char	*value;
	int		name_len;

	value = ft_strchr(var, '=');
	if (value)
	{
		name_len = value - var + 1;
		if (!(tmp = malloc(sizeof(char *) * name_len)))
			return (-1);
		ft_memccpy(tmp, var, '=', name_len);
		tmp[name_len] = '\0';
		ft_putstr_fd(tmp, 1);
		free(tmp);
		++value;
		tmp = put_in_quotes(value);
		ft_putendl_fd(tmp, 1);
		free(tmp);
	}
	else
		ft_putendl_fd(var, 1);
	return (0);
}
