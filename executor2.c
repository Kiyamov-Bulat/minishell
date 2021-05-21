#include "executor.h"

int		execute_cd(char *new_path, char **env)
{
	int		res;
	char	*cur_pwd;
	char	*var_path;

	if (!new_path)
		return (0);
	cur_pwd = get_cur_path();
	res = chdir(new_path);
	if (res < 0)
		handle_cd_error(new_path);
	else
	{
		var_path = ft_strjoin("OLDPWD=", cur_pwd);
		change_evn_var(var_path, 6, env);
		free(var_path);
		free(cur_pwd);
		cur_pwd = get_cur_path();
		var_path = ft_strjoin("PWD=", cur_pwd);
		change_evn_var(var_path, 3, env);
		free(var_path);
	}
	free(cur_pwd);
	return (res < 0 ? 1 : 0);
}

int		open_redirect(t_cmd *cmd, int direct)
{
	int err;

	if (direct == 1)
	{
		cmd->fd[1] = open(cmd->file_in, O_CREAT | O_RDWR | \
				(cmd->fl_append ? O_APPEND : O_TRUNC), 0666);
		if (cmd->fd[1] < 0)
			return (1);
		err = dup2(cmd->fd[1], 1) == -1;
		err |= close(cmd->fd[1]);
	}
	else if (direct == 0)
	{
		cmd->fd[0] = open(cmd->file_out, O_RDONLY);
		if (cmd->fd[0] < 0)
			return (1);
		err = dup2(cmd->fd[0], 0) == -1;
		err |= close(cmd->fd[0]);
	}
	else
		return (1);
	return (err);
}

void	open_empty_pipe(int tmp_fd[])
{
	pipe(tmp_fd);
	dup2(tmp_fd[0], 0);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}

int		handle_redirect(t_cmd *cmd, int tmp_fd[])
{
	extern int g_last_res;

	if (cmd->file_in && open_redirect(cmd, 1))
	{
		g_last_res = handle_error(FD_ERROR, cmd->file_in);
		return (1);
	}
	if (cmd->file_out && open_redirect(cmd, 0))
	{
		g_last_res = handle_error(FD_ERROR, cmd->file_out);
		dup2(tmp_fd[1], 1);
		return (1);
	}
	return (0);
}

void	execute_in_current_process(t_cmd *cmd, char ***env)
{
	extern int g_last_res;

	if (ft_strequal(cmd->command, "cd"))
		g_last_res = execute_cd(cmd->args[1], *env);
	else if (ft_strequal(cmd->command, "unset"))
		g_last_res = ft_unset(cmd->args + 1, env);
	else if (ft_strequal(cmd->command, "export"))
		g_last_res = ft_export(cmd->args + 1, env);
	else if (ft_strequal(cmd->command, "exit"))
		g_last_res = ft_exit(cmd->args + 1);
	if (g_last_res == ENOMEM)
		handle_error(MALLOC_ERROR, cmd->command);
}
