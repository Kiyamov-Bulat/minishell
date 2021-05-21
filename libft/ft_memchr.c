#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*ps;

	uc = (unsigned char)c;
	ps = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*ps == uc)
			return ((void *)ps);
		ps++;
	}
	return (NULL);
}
