#include "minishell.h"
#include "executor.h"

static void		prepare_to_work(t_tools **tools, char ***clone_env, \
		char **envp, void *unused)
{
	char *shlvl;

	if (!(*tools = malloc(sizeof(t_tools))))
	{
		handle_error(MALLOC_ERROR, "minishell");
		exit(ENOMEM);
	}
	(*tools)->tmp_fd[0] = dup(0);
	(*tools)->tmp_fd[1] = dup(1);
	if (!(*clone_env = clone_envp(envp)))
	{
		handle_error(MALLOC_ERROR, "minishell");
		exit(ENOMEM);
	}
	shlvl = get_env_var("SHLVL", *clone_env);
	increase_shlvl(shlvl, clone_env);
	(void)unused;
}

static void		set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void			show_promt(void)
{
	write(1, G_PRESTR, ft_strlen(G_PRESTR));
}

int				main(int argc, char **argv, char **envp)
{
	t_cmd		**cmd;
	t_tools		*tools;
	char		**envtmp;
	int			i;

	prepare_to_work(&tools, &envtmp, envp, argv[argc]);
	while (1)
	{
		set_signal();
		show_promt();
		if ((cmd = parse_cmd_line(envtmp)) == NULL)
			minishell_exit();
		if ((cmd[0]->command[0] != 0 || cmd[1]) && !set_last_red_file(cmd))
		{
			i = -1;
			while (cmd[++i])
			{
				if (prepare_cmd(cmd[i], envtmp))
					break ;
				executor(cmd[i], &envtmp, tools);
			}
		}
		free_cmd(cmd);
	}
	return (0);
}
