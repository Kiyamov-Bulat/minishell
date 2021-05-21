#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ns;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if ((ns = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	res = ns;
	while ((*ns = *s1) != '\0')
	{
		ns++;
		s1++;
	}
	while ((*ns = *s2) != '\0')
	{
		ns++;
		s2++;
	}
	return (res);
}
