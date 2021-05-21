#include "minishell.h"

int	ft_cd(char *path)
{
	return (chdir(path));
}
