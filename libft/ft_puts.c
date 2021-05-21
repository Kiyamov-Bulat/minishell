#include "libft.h"

int	ft_puts(char *s)
{
	return (ft_putstr_fd(s, 1));
}
