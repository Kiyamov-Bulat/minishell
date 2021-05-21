#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t size;

	size = dstsize;
	while (*dst != '\0' && size != 0)
	{
		size--;
		dst++;
	}
	if (src == NULL)
		src++;
	return (dstsize - size + ft_strlcpy(dst, src, size));
}
