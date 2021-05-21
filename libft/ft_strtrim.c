#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	const char	*sset;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	sset = set;
	while (start <= end && *sset != '\0')
	{
		sset = set;
		while (*sset && *sset != s1[start])
			sset++;
		*sset != '\0' ? start++ : 0;
	}
	sset = set;
	while (*sset != '\0')
	{
		sset = set;
		while (*sset && *sset != s1[end])
			sset++;
		*sset != '\0' ? end-- : 0;
	}
	return (ft_substr(s1, start, (int)(end - start) < 0 ? 0 : end - start + 1));
}
