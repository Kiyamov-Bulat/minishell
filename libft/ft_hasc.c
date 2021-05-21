#include "libft.h"

int	ft_hasc(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	return (*s != '\0');
}
