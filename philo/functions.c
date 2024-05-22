#include "philo.h"

int     ft_atoi(char *str)
{
	int	result;
	int	i;
	int	signal;

	i = 0;
	result = 0;
	signal = 1;
	while (((str[i] == 32) || (str[i] >= 7 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * signal);
}

int     ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static long     is_negative(const char *str)
{
	long	i;
	long	signal;

	i = 0;
	signal = 1;
	while (str[i] != '\0' && !ft_isdigit(str[i]))
	{
		if (str[i] == '-')
			signal = -1;
		else if (str[i] == '+')
			signal = 1;
		i++;
	}
	return (signal);
}

long    ft_atol(char *str)
{
	long	result;
	long	i;
	long	signal;

	i = 0;
    result = 0;
    signal = 1;
	signal = (is_negative(str));
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * signal);
}

