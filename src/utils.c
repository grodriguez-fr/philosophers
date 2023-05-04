#include "philosophers.h"

void ft_putstr_err(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write (1, str, i);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int			res;
	int			sign;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + sign * (str[i++] - '0');
	return (res);
}
