#include "minishell.h"

static char *g_bufp = 0;
static int	g_n = 0;
static int	g_last_c = '\n';

/*
** Buffered read from stdin
**
** Returns: unsigned char
** 			or EOF == 0; ERROR == -1
*/

int		ft_getch(void)
{
	static char buf[BUFFER_SIZE >= 0 ? BUFFER_SIZE : 0];
	extern char *g_bufp;
	extern int	g_n;

	if (g_n == 0)
	{
		g_n = read(0, buf, BUFFER_SIZE);
		g_bufp = buf;
	}
	while (g_n == 0 && g_last_c != '\n')
	{
		g_n = read(0, buf, BUFFER_SIZE);
		g_bufp = buf;
	}
	if (--g_n >= 0)
	{
		g_last_c = (unsigned char)*g_bufp++;
		return (g_last_c);
	}
	else
		return (g_n == -1 ? 0 : -1);
}

/*
** Returns character to the buffer
*/

void	ft_ungetch(void)
{
	extern char *g_bufp;
	extern int	g_n;

	g_bufp--;
	g_n++;
	g_last_c = (unsigned char)*g_bufp;
}
