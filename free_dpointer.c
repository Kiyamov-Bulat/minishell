#include "minishell.h"

int	free_dpointer(void ***p, size_t nmemb)
{
	void **dp;

	dp = *p;
	while (nmemb--)
		free(dp[nmemb]);
	free(*p);
	*p = NULL;
	return (1);
}
