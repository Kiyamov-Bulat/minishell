#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	unsigned char	cc;

	cc = (unsigned char)c;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (n-- > 0)
	{
		*cdst++ = *csrc;
		if (*csrc++ == cc)
			return ((void *)cdst);
	}
	return (NULL);
}
