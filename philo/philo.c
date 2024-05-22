#include "philo.h"

void	*all_routines(void *arg)
{

}

int	main(int argc, char **argv)
{
	if (argc == 4 || argc == 5)
	{
		int			i = 0;
		int			philo_nbr = ft_atoi(argv[1]);
		pthread_t	*threads;
		pthread_mutex_t     mutex;
		pthread_mutex_init(&mutex, NULL);
		while (threads < philo_nbr)
		{
			if ((pthread_create(&threads[i], NULL, &all_routines, NULL)) != 0)
			{
				perror("Failed to create thread");
				return (-1);
			}
			i++;
		}
		while (threads < philo_nbr)
		{
			if ((pthread_create(threads, NULL, &all_routines, NULL)) != 0)
			{
				perror("Failed to create thread");
				return (-1);
			}
			i++;
		}
		pthread_mutex_destroy(&mutex);
	}
	else
	{
		printf("Error\nInvalid number of arguments");
		return(-1);
	}
	return (0);
}
