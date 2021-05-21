#include "libft.h"

int	ft_indexof(const char *s, const char *ss, int from_index)
{
	int		index;
	char	*f;

	if (s == NULL || ss == NULL || from_index < 0)
		return (-1);
	index = from_index;
	while (index-- && *s)
		s++;
	f = ft_strstr(s, ss);
	if (f == NULL)
		return (-1);
	else
		return (from_index + (f - s));
}
