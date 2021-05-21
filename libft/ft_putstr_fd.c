#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return (write(fd, s, ft_strlen(s)));
	return (-1);
}
