#include "minishell.h"

char		*get_abs_path(char *dir, char *file_name)
{
	char *t;
	char *r;

	r = NULL;
	if ((t = ft_strjoin(dir, "/")) != NULL)
	{
		r = ft_strjoin(t, file_name);
		free(t);
	}
	return (r);
}

char		*get_abs_parent(char *dir)
{
	char *tmp;

	tmp = ft_strrchr(dir, '/');
	return (join_path("", dir, tmp - dir));
}

int			is_curdir(char *p)
{
	return ((p)[0] == '.' && (p)[1] == '/');
}

int			is_pardir(char *p)
{
	return ((p)[0] == '.' && (p)[1] == '.' && (p)[2] == '/');
}

int			is_path(char *p)
{
	return (ft_strchr((p), '/') != NULL);
}
