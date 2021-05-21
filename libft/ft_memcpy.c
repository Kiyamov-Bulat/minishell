#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *cdst;
	char *csrc;

	cdst = (char *)dest;
	csrc = (char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n-- > 0)
		*cdst++ = *csrc++;
	return (dest);
}
