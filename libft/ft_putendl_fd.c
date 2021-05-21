#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int n;

	n = -1;
	if (s != NULL)
	{
		n = ft_putstr_fd(s, fd);
		if (n != -1)
			n += ft_putchar_fd('\n', fd);
	}
	return (n);
}
