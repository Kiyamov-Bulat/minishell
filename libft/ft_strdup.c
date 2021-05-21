#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ns;

	len = ft_strlen(s);
	if ((ns = (char *)malloc(len + 1)) != NULL)
		ft_strlcpy(ns, s, len + 1);
	return (ns);
}
