#include "philo.h"

//Check if input is a nbr OK
//Check for negatives OK
//Check for INT_MAX OK

int	is_digit(int c)
{
	return(c >= '0' && c <= '9');
}

int	is_in_range(char **argv)
{
	long	j;

	j = 1;
	while (argv[j])
	{
		if (ft_atol(argv[j]) > INT_MAX || argv[j] <= 0)
        {
            printf("Error\nThe input must be in the range: positives, non-zero and less than MAX_INT numbers\n");
            return (1);
        }
		j++;
	}
	return (0);
}

int     is_nbr(char **argv)
{
	int     i;
	int     j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] == '+')
				i++;
			if (!is_digit(argv[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int     check_args(int argc, char **argv)
{
    if (!(argc == 5 || argc == 6))
    {
        printf("Invalid arguments.\nIt must be: ./philos  [nbr_of_philos]  [time_to_die]  [time_to_eat]  [time_to_sleep]  [nbr_of_meals]\n");
        return (1);
    }
    if (is_nbr(argv) || is_in_range(argv)) 
        return (1);
    return (0);
}