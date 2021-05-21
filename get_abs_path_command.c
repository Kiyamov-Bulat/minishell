#include "minishell.h"

static char		*file_in_path(char *command, char **envpath)
{
	int				i;
	DIR				*cur_dir;
	struct dirent	*entry;

	i = 0;
	while (envpath[i])
	{
		cur_dir = opendir(envpath[i]);
		if (cur_dir)
		{
			errno = 0;
			while ((entry = readdir(cur_dir)) != NULL \
					&& !ft_strequal(entry->d_name, command))
				;
			closedir(cur_dir);
			if (entry != NULL)
				return (get_abs_path(envpath[i], command));
			else if (errno != 0)
				return (NULL);
		}
		else
			return (NULL);
		++i;
	}
	return (NULL);
}

char			*join_path(char *p1, char *p2, size_t p2_end)
{
	char *newp;

	p2[p2_end] = '\0';
	if (p2[0] == '/')
		newp = ft_strjoin(p1, p2);
	else
		newp = get_abs_path(p1, p2);
	p2[p2_end] = '/';
	return (newp);
}

static int		init_abs_path(char *cmd, char *cdir, char **abs_path)
{
	char *tmp;

	if (cmd[0] == '/')
	{
		*abs_path = ft_strdup("");
		return (1);
	}
	else if (is_pardir(cmd))
	{
		*abs_path = get_abs_parent(cdir);
		return (3);
	}
	else if (is_curdir(cmd))
	{
		*abs_path = ft_strdup(cdir);
		return (2);
	}
	else
	{
		tmp = ft_strchr(cmd, '/');
		*abs_path = join_path(cdir, cmd, tmp - cmd);
		return (tmp - cmd + 1);
	}
}

static char		*parse_part_of_path(char *cmd, char **path)
{
	char *tmp;
	char *tmp2;

	if (is_pardir(cmd))
	{
		if ((tmp = ft_strrchr(*path, '/')) != NULL)
			(*path)[tmp - *path] = '\0';
		return (cmd + 3);
	}
	else if (is_curdir(cmd))
		return (cmd + 2);
	else
	{
		tmp = ft_strchr(cmd, '/');
		tmp2 = *path;
		if (tmp)
			*path = join_path(*path, cmd, tmp - cmd);
		else
			*path = get_abs_path(*path, cmd);
		free(tmp2);
		return (tmp ? tmp + 1 : 0);
	}
}

char			*get_abs_path_command(char *cmd, char **env)
{
	char	*cdir;
	char	*abs_path;
	char	**envpath;

	cdir = get_cur_path();
	envpath = parse_path(env);
	if (!cmd || !cdir)
		return (NULL);
	if (is_path(cmd))
	{
		cmd += init_abs_path(cmd, cdir, &abs_path);
		while (cmd && abs_path)
			cmd = parse_part_of_path(cmd, &abs_path);
	}
	else
	{
		errno = 0;
		if (!envpath || (abs_path = file_in_path(cmd, envpath)) == NULL)
			abs_path = get_abs_path(cdir, cmd);
	}
	free(cdir);
	free_dpointer_no_size((void **)envpath);
	return (abs_path);
}
