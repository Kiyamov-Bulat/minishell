#include "libft.h"

char	*ft_realloc_str(char **buf, unsigned long int size)
{
	char				*new_buf;
	char				*t;
	unsigned long int	i;

	if ((new_buf = (char *)malloc(size + 1)) == NULL)
		return (NULL);
	i = 0;
	t = *buf;
	while (i < size && (new_buf[i] = t[i]) != '\0')
		i++;
	new_buf[size] = '\0';
	free_n_null(buf);
	return (new_buf);
}

void	free_n_null(char **buf)
{
	free(*buf);
	*buf = NULL;
}
