#include "libft.h"

char	*ft_strcpy(char *dst, char *src)
{
	char *r;

	r = dst;
	while ((*dst++ = *src++))
		;
	return (r);
}
