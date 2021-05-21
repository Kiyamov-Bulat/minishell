#include "minishell.h"

int		is_empty_files(char *file_in, char *file_out)
{
	if (file_in && !*file_in)
		return (1);
	if (file_out && !*file_out)
		return (1);
	return (0);
}

int		syntax_error(t_cmd *cmd)
{
	extern int g_last_res;

	(void)cmd;
	ft_putendl_fd("minishell: syntax error near unexpected token", \
			STDERR_FILENO);
	return ((g_last_res = 258));
}
