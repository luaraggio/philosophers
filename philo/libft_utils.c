#include "philo.h"

int     ft_atoi(char *str)
{
	unsigned int	result;
	int	i;

	i = 0;
	result = 0;
	while (((str[i] == 32) || (str[i] >= 7 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

long	is_negative(const char *str)
{
	long	i;
	long	sign;

	i = 0;
	sign = 1;
	while (str[i] != '\0' && !is_digit(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		else if (str[i] == '+')
			sign = 1;
		i++;
	}
	return (sign);
}

long	ft_atol(const char *str)
{
	long	value;
	long	i;
	long	sign;

	value = 0;
	i = 0;
	sign = (is_negative(str));
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (is_digit(str[i]))
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

void	ft_bzero(void *s, size_t n)
{
	char	*a;

	a = (char *) s;
	while (n > 0)
	{
		a[n - 1] = '\0';
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if ((nmemb) && (size * nmemb > 0) && ((nmemb * size) / nmemb != size))
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, (nmemb * size));
	return (str);
}