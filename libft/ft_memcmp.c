#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *cs1;
	unsigned char *cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (*cs1 != *cs2)
			return ((int)*cs1 - *cs2);
		cs1++;
		cs2++;
	}
	return (0);
}
