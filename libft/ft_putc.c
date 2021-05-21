#include "libft.h"

int	ft_putc(char c)
{
	return (ft_putchar_fd(c, 1));
}
