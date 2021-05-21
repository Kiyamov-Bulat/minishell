#include "libft.h"

static	int	ft_sethas(const char *set, char c)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

static char	**alloc_str_arr(const char *s, const char *set)
{
	long int i;
	long int size;

	i = 0;
	size = 1;
	while (s[i])
	{
		if (ft_sethas(set, s[i]) && !ft_sethas(set, s[i - 1]))
			size++;
		i++;
	}
	i != 0 && !ft_sethas(set, s[i - 1]) ? size++ : 0;
	return ((char **)malloc(size * sizeof(char *)));
}

static int	ft_safely_fill(char const *s, char ***arr, int last, int curr)
{
	if (last != curr - 1)
	{
		if (!(**arr = ft_substr(s, last + 1, curr - last - 1)))
			return (1);
		else
			(*arr)++;
	}
	return (0);
}

char		**ft_ssplit(char const *s, const char *set)
{
	char		**t;
	char		**res;
	long int	i;
	long int	last;

	if (s == NULL)
		return (NULL);
	i = 0;
	last = -1;
	res = alloc_str_arr(s, set);
	t = res;
	while (res != NULL && (i == 0 || s[i - 1] != '\0'))
		if (ft_sethas(set, s[i]) || s[i] == '\0')
		{
			if (ft_safely_fill(s, &t, last, i))
			{
				ft_free_matrix((void ***)&res);
				return (NULL);
			}
			last = i++;
		}
		else
			i++;
	res != NULL ? *t = NULL : 0;
	return (res);
}
