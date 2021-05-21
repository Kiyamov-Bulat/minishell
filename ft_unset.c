#include "minishell.h"

static int	restruct_envp(char ***envp, int n)
{
	char	**env;

	env = *envp;
	while (env[n])
	{
		if (env[n + 1])
		{
			free(env[n]);
			env[n] = ft_strdup(env[n + 1]);
			if (!(env[n]))
				return (ENOMEM);
			++n;
		}
		else
		{
			free(env[n]);
			env[n] = NULL;
		}
	}
	return (0);
}

static int	error(char *err_msg)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (1);
}

int			ft_unset(char **vars, char ***envp)
{
	int		i;
	int		j;
	char	*eqsign;
	char	**env;
	size_t	name_sz;

	i = -1;
	env = *envp;
	while (vars[++i])
	{
		j = -1;
		while (env[++j])
		{
			eqsign = ft_strchr(env[j], '=');
			name_sz = ft_strlen(vars[i]);
			if (!is_correct_name(vars[i], name_sz))
				return (error("minishell: unset: not a valid identifier"));
			if (eqsign && name_sz == (size_t)(eqsign - env[j]) \
					&& (ft_strncmp(env[j], vars[i], eqsign - env[j])) == 0
						&& restruct_envp(envp, j))
				return (1);
		}
	}
	return (0);
}
