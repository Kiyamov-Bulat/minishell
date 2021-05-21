#include "minishell.h"

static void	swap_files(t_cmd *c1, t_cmd *c2)
{
	t_cmd t;

	free(c2->args[0]);
	c2->args[0] = ft_strdup("");
	free(c2->command);
	c2->command = ft_strdup(c1->command);
	t.file_in = c1->file_in;
	t.file_out = c1->file_out;
	t.fl_append = c1->fl_append;
	if (c2->file_in)
	{
		c1->file_in = c2->file_in;
		c1->fl_append = c2->fl_append;
		c2->file_in = t.file_in;
		c2->fl_append = t.fl_append;
	}
	else
	{
		c1->file_out = c2->file_out;
		c2->file_out = t.file_out;
	}
	c1->fl_pipe = c2->fl_pipe;
}

static void	del_elem(t_cmd **cmd, int index)
{
	delcmd(cmd[index]);
	while (cmd[index + 1] != NULL)
	{
		cmd[index] = cmd[index + 1];
		index++;
	}
	cmd[index] = NULL;
}

static void	set_new_direct(t_cmd *true_cmd, t_cmd *file_cmd)
{
	if (!true_cmd->file_in)
	{
		true_cmd->file_in = ft_strdup(file_cmd->file_in);
		true_cmd->fl_append = file_cmd->fl_append;
	}
	else
		true_cmd->file_out = ft_strdup(file_cmd->file_out);
	true_cmd->fl_pipe = true_cmd->fl_pipe || file_cmd->fl_pipe;
}

static char	*set_file(t_cmd *true_cmd, t_cmd *file_cmd)
{
	int fd;

	if ((!true_cmd->file_in && file_cmd->file_in) \
			|| (!true_cmd->file_out && file_cmd->file_out))
		set_new_direct(true_cmd, file_cmd);
	else
	{
		swap_files(true_cmd, file_cmd);
		if (file_cmd->file_in)
		{
			fd = open(file_cmd->file_in, O_CREAT | O_WRONLY \
					| (file_cmd->fl_append ? O_APPEND : O_TRUNC), 0666);
			if (fd < 0)
				return (file_cmd->file_in);
		}
		else
		{
			fd = open(file_cmd->file_out, O_RDONLY);
			if (fd < 0)
				return (file_cmd->file_out);
		}
		close(fd);
	}
	return (NULL);
}

int			set_last_red_file(t_cmd **cmd)
{
	int		i;
	char	*incorrect_file;
	t_cmd	*true_cmd;

	i = -1;
	true_cmd = NULL;
	while (cmd[++i])
	{
		if (is_empty_files(cmd[i]->file_in, cmd[i]->file_out))
			return (syntax_error(cmd[i]));
		if (cmd[i]->command[0] != '\0')
			true_cmd = cmd[i];
		else if (true_cmd != NULL && (cmd[i]->file_in || cmd[i]->file_out))
		{
			merge_dpointer((void ***)&true_cmd->args, \
					(void **)cmd[i]->args + 1);
			cmd[i]->args[1] = NULL;
			if ((incorrect_file = set_file(true_cmd, cmd[i])) != NULL)
				return (handle_error(FD_ERROR, incorrect_file));
			del_elem(cmd, i--);
		}
		else
			return (handle_error(WRONG_COMMAND, cmd[i]->command));
	}
	return (0);
}
