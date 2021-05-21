#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-' ? -sign : sign;
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str++ - '0';
		if (res > LONG_MAX)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (res * sign);
}
