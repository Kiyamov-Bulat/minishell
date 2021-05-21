#include "executor.h"

static int	call_func(t_cmd *cmd, char **envp)
{
	char	**args;
	int		exec_ret;

	args = cmd->args + 1;
	if (ft_strequal(cmd->command, "echo"))
		exec_ret = ft_echo(args);
	else if (ft_strequal(cmd->command, "cd"))
		exec_ret = execute_cd(*args, envp);
	else if (ft_strequal(cmd->command, "unset"))
		exec_ret = ft_unset(args, &envp);
	else if (ft_strequal(cmd->command, "exit"))
		exec_ret = ft_exit(args);
	else if (ft_strequal(cmd->command, "export"))
		exec_ret = ft_export(args, &envp);
	else if (ft_strequal(cmd->command, "env"))
		exec_ret = ft_env(args, envp);
	else if (ft_strequal(cmd->command, "pwd"))
		exec_ret = ft_pwd();
	else if ((exec_ret = execve(cmd->args[0], cmd->args, envp)) < 0)
		exec_ret = handle_error(WRONG_COMMAND, cmd->command);
	return (exec_ret);
}

static void	execute(t_cmd *command, char **envp)
{
	int			exec_ret;
	int			pid;
	int			status;
	extern int	g_last_res;

	pid = fork();
	if (pid == 0)
	{
		exec_ret = call_func(command, envp);
		exit(exec_ret);
	}
	else if (pid < 0)
		exit(1);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (g_last_res < 126)
			g_last_res = WEXITSTATUS(status);
	}
}

static void	execute_with_pipe(t_cmd *cmd, char **envp)
{
	int			exec_ret;
	int			pid;
	int			status;

	pipe(cmd->fd);
	if ((pid = fork()) == 0)
	{
		if (!cmd->file_in)
			dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		exec_ret = call_func(cmd, envp);
		close(cmd->fd[1]);
		exit(exec_ret);
	}
	else if (pid < 0)
		exit(1);
	else
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[1]);
		waitpid(pid, &status, WUNTRACED);
		close(cmd->fd[0]);
		if (g_last_res < 126)
			g_last_res = WEXITSTATUS(status);
	}
}

void		executor(t_cmd *cmd, char ***envp, t_tools *tools)
{
	g_last_res = 0;
	signal(SIGINT, input_signal_handler);
	signal(SIGQUIT, input_signal_handler);
	g_prepipe = g_prepipe || cmd->fl_pipe;
	if (handle_redirect(cmd, tools->tmp_fd))
	{
		if (cmd->fl_pipe)
			open_empty_pipe(cmd->fd);
		return ;
	}
	if ((ft_strequal(cmd->command, "cd")	\
	|| ft_strequal(cmd->command, "exit")	\
	|| ft_strequal(cmd->command, "export")	\
	|| ft_strequal(cmd->command, "unset")) && !g_prepipe && !(cmd->fl_pipe))
		execute_in_current_process(cmd, envp);
	else if (cmd->fl_pipe)
		execute_with_pipe(cmd, *envp);
	else
		execute(cmd, *envp);
	if (!cmd->fl_pipe)
		dup2(tools->tmp_fd[0], 0);
	dup2(tools->tmp_fd[1], 1);
	g_prepipe = cmd->fl_pipe;
}
