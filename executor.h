#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "minishell.h"

typedef struct	s_tools
{
	int			tmp_fd[2];
	int			exit_code;
}				t_tools;

int				g_last_res;
int				g_prepipe;

int				execute_cd(char *new_path, char **env);
int				open_redirect(t_cmd *cmd, int direct);
void			open_empty_pipe(int tmp_fd[]);
int				handle_redirect(t_cmd *cmd, int tmp_fd[]);
void			execute_in_current_process(t_cmd *cmd, char ***env);
void			handle_cd_error(char *path);
int				handle_exit_error(char *path);
void			executor(t_cmd *cmd, char ***envp, t_tools *tools);
void			signal_handler(int sig);
void			input_signal_handler(int sig);
void			show_promt();
int				minishell_exit();
int				change_evn_var(char *var, size_t name_size, char **env);
#endif
