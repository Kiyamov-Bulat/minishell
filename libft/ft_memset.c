#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*ps;
	unsigned char	cc;

	cc = (unsigned char)c;
	ps = (char *)s;
	while (n-- > 0)
		*ps++ = cc;
	return (s);
}
