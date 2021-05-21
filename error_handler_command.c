#include "minishell.h"

void		handle_cd_error(char *path)
{
	char	*err_str;
	char	*err_tmp;

	err_str = ft_strjoin("minishell: cd: ", path);
	err_tmp = err_str;
	err_str = ft_strjoin(err_str, ": ");
	free(err_tmp);
	err_tmp = err_str;
	err_str = ft_strjoin(err_str, strerror(errno));
	free(err_tmp);
	err_tmp = err_str;
	err_str = ft_strjoin(err_str, "\n");
	free(err_tmp);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	free(err_str);
}

int			handle_exit_error(char *path)
{
	char	*err_str;
	char	*err_tmp;

	err_str = ft_strjoin("minishell: exit: ", path);
	err_tmp = err_str;
	err_str = ft_strjoin(err_str, ": ");
	free(err_tmp);
	err_tmp = err_str;
	err_str = ft_strjoin(err_str, "numeric argument required");
	free(err_tmp);
	err_tmp = err_str;
	err_str = ft_strjoin(err_str, "\n");
	free(err_tmp);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	free(err_str);
	return (255);
}
