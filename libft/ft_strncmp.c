#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned const char *us1;
	unsigned const char *us2;

	i = 0;
	us1 = (unsigned const char *)s1;
	us2 = (unsigned const char *)s2;
	while (i++ < n)
	{
		if (!*us1 || *us1 != *us2)
			return (*us1 - *us2);
		us1++;
		us2++;
	}
	return (0);
}
