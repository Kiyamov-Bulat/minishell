#include "minishell.h"

char			**clone_envp(char **envp)
{
	char	**envtmp;
	int		i;
	int		len;

	i = 0;
	while (envp[i])
		++i;
	len = i;
	if (!(envtmp = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!(envtmp[i] = ft_strdup(envp[i])))
		{
			free_dpointer_no_size((void **)envtmp);
			return (NULL);
		}
		++i;
	}
	envtmp[i] = NULL;
	return (envtmp);
}

void			bubblesort(char **strs)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*temp;

	size = get_size(strs);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(strs[j], strs[j + 1], ft_strlen(strs[j])) > 0)
			{
				temp = strs[j];
				strs[j] = strs[j + 1];
				strs[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char			**ft_join_dpoiner(char **dp1, char **dp2)
{
	int		i;
	int		sz;
	char	**res;

	i = 0;
	sz = get_size(dp1) + get_size(dp2) + 1;
	if ((res = (char **)malloc(sizeof(char *) * sz)) == NULL)
		return (NULL);
	while (*dp1)
		res[i++] = *dp1++;
	while (*dp2)
		res[i++] = *dp2++;
	res[i] = NULL;
	return (res);
}

int				ft_insert(char ***dst, char **src, int pos)
{
	char	*s_on_pos;
	char	**tmp;
	char	**mid;
	int		res;

	tmp = *dst;
	if ((s_on_pos = tmp[pos]) != NULL)
	{
		tmp[pos] = NULL;
		if ((mid = ft_join_dpoiner(tmp, src)) == NULL)
			return (-1);
		tmp[pos] = s_on_pos;
		if ((*dst = ft_join_dpoiner(mid, tmp + pos)) == NULL)
			return (-1);
		free(mid);
	}
	else if ((*dst = ft_join_dpoiner(tmp, src)) == NULL)
		return (-1);
	free(tmp);
	res = (pos + get_size(src));
	return (res);
}
