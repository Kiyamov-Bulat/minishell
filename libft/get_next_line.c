#include "libft.h"

static int	read_chunk_size(int fd, char *chunk, int *stop_index)
{
	int		i;
	int		c;

	i = 0;
	while (i < CHUNK_SIZE && (c = ft_getchar(fd)) > -1
			&& c != '\n')
	{
		*chunk++ = c;
		i++;
	}
	*stop_index = i;
	*chunk = '\0';
	return (c);
}

static int	read_line(int fd, char **line)
{
	int					c;
	int					si;
	unsigned long int	size;

	size = CHUNK_SIZE;
	if ((*line = (char *)malloc(size + 1)) == NULL)
		return (-2);
	while ((c = read_chunk_size(fd, *line + (size - CHUNK_SIZE), &si)) != '\n'
		&& c > -1)
		if ((*line = ft_realloc_str(line, size += CHUNK_SIZE)) == NULL)
			return (-2);
	if (si != CHUNK_SIZE && c > -2)
		if ((*line = ft_realloc_str(line, size - (CHUNK_SIZE - si))) == NULL)
			return (-2);
	return (c);
}

int			get_next_line(int fd, char **line)
{
	int c;

	if (BUFFER_SIZE > 0)
	{
		c = read_line(fd, line);
		if (c == '\n')
			return (1);
		else if (c == -1)
			return (0);
		free_n_null(line);
		return (-1);
	}
	else
	{
		*line = NULL;
		if (BUFFER_SIZE == 0)
			return (0);
		return (-1);
	}
}
