#include "minishell.h"

int		free_dpointer_no_size(void **p)
{
	int i;

	i = 0;
	while (p && p[i])
		free(p[i++]);
	free(p);
	return (1);
}

void	free_cmd(t_cmd **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		free(cmd[i]->file_in);
		free(cmd[i]->file_out);
		free(cmd[i]->command);
		while (cmd[i]->args[j])
		{
			free(cmd[i]->args[j]);
			++j;
		}
		free(cmd[i]->args);
		free(cmd[i]);
		++i;
	}
	free(cmd);
}
