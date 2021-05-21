#include "minishell.h"

int	ft_echo(char **args)
{
	int fl_n;
	int	fl_f;

	fl_n = 0;
	fl_f = 0;
	while (*args && ft_strequal(*args, "-n") && (fl_n = 1))
		args++;
	while (*args)
	{
		if (**args != '\0')
		{
			if (fl_f && ft_putchar_fd(' ', 1) == -1)
				return (errno);
			else
				fl_f = 1;
			if (ft_puts(*args) == -1)
				return (errno);
		}
		args++;
	}
	if (!fl_n && ft_putchar_fd('\n', 1) == -1)
		return (errno);
	return (0);
}
