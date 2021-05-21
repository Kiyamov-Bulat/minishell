#include "libft.h"

static char	**alloc_str_arr(const char *s, char c)
{
	long int i;
	long int size;

	i = 0;
	size = 1;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			size++;
		i++;
	}
	i != 0 && s[i - 1] != c ? size++ : 0;
	return ((char **)malloc(size * sizeof(char *)));
}

static int	ft_free_arr(char ***arr)
{
	int		i;
	char	**a;

	i = 0;
	a = *arr;
	while (a[i])
		free(a[i++]);
	free(a);
	*arr = NULL;
	return (1);
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

char		**ft_split(char const *s, char c)
{
	char		**t;
	char		**res;
	long int	i;
	long int	last;

	if (s == NULL)
		return (NULL);
	i = 0;
	last = -1;
	res = alloc_str_arr(s, c);
	t = res;
	while (res != NULL && (i == 0 || s[i - 1] != '\0'))
		if (s[i] == c || s[i] == '\0')
		{
			if (ft_safely_fill(s, &t, last, i))
			{
				ft_free_arr(&res);
				return (NULL);
			}
			last = i++;
		}
		else
			i++;
	res != NULL ? *t = NULL : 0;
	return (res);
}
