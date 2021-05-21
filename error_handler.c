#include "minishell.h"
#include "executor.h"
#include <sys/stat.h>

static char		*create_error_message(const char *command)
{
	char *str;
	char *str_tmp;

	str = ft_strjoin("minishell: ", command);
	str_tmp = str;
	str = ft_strjoin(str, ": ");
	free(str_tmp);
	return (str);
}

static void		show_error_message(const char *command, const char *message)
{
	char *str;
	char *str_tmp;

	str = create_error_message(command);
	str_tmp = str;
	str = ft_strjoin(str, message);
	free(str_tmp);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(str);
}

static void		handle_wrong_command(const char *command, int *ret)
{
	char		*slash;
	struct stat	s_inf;

	*ret = 1;
	if (!(stat(command, &s_inf)))
	{
		*ret = 126;
		if (S_ISDIR(s_inf.st_mode))
			show_error_message(command, "is a directory");
		else if (S_ISREG(s_inf.st_mode) && (ft_strncmp(command, "./", 2) == 0))
			show_error_message(command, "Permission denied");
		else
		{
			*ret = 127;
			show_error_message(command, "command not found");
		}
	}
	else
	{
		*ret = 127;
		if (!(slash = ft_strrchr(command, '/')))
			show_error_message(command, "command not found");
		else if (*(slash + 1) != '\0')
			show_error_message(command, "No such file or directory");
	}
}

int				handle_error(int code, const char *command)
{
	int			ret;

	ret = 1;
	if (code == WRONG_COMMAND)
		handle_wrong_command(command, &ret);
	else if (code == MANY_ARGS)
		show_error_message(command, "too many arguments");
	else if (code == MALLOC_ERROR)
		show_error_message(command, strerror(errno));
	else if (code == FD_ERROR)
		show_error_message(command, strerror(errno));
	else if (code == SYMB_CODE)
		show_error_message(command, "numeric argument required");
	return (ret);
}
