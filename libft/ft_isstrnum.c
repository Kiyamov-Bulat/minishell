#include "libft.h"

int	ft_isstrnum(const char *s)
{
	int i;

	i = 0;
	while (*s && ft_isdigit(*s++))
		i = 1;
	return (*s == '\0' && i != 0);
}
