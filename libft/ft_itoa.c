#include "libft.h"

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	len;
	unsigned int	un;
	unsigned int	ut;

	len = (n < 0) ? 2 : 1;
	un = (n < 0) ? -((unsigned int)n) : (unsigned int)n;
	ut = un;
	while ((ut /= 10) > 0)
		len++;
	if ((s = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	*s++ = un % 10 + '0';
	while ((un /= 10) > 0)
		*s++ = un % 10 + '0';
	n < 0 ? *s++ = '-' : 0;
	*s = '\0';
	s = (s - len);
	while (--len > un)
	{
		ut = *(s + un);
		*(s + un++) = *(s + len);
		*(s + len) = ut;
	}
	return (s);
}
