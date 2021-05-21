#include "libft.h"

int	ft_free_matrix(void ***arr)
{
	int		i;
	void	**a;

	i = 0;
	a = *arr;
	while (a[i])
		free(a[i++]);
	free(a);
	*arr = NULL;
	return (1);
}
