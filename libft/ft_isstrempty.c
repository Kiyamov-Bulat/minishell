#include "libft.h"

int	ft_isstrempty(const char *s)
{
	if (s == NULL)
		return (1);
	while (*s && ft_isspace(*s))
		s++;
	return (!*s);
}
