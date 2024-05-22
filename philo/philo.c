#include "philo.h"

void	*all_routines()
{
	printf("I'm a philosopher and everithyng is working.\n");
	return (NULL);
}

/*t_philo		init_philo_struct()
{

}*/

int	main(int argc, char **argv)
{
	(void)argc;
	if (argc == 5 || argc == 6)
	{
		int			i = 0;
		int			philo_nbr = ft_atoi(argv[1]);
		pthread_t	*threads;
		pthread_mutex_t     mutex;
		pthread_mutex_init(&mutex, NULL);
		while (i < philo_nbr)
		{
			//Antes de criar, preciso alocar a quantidade de filósofos
			if ((pthread_create(threads + i, NULL, &all_routines, NULL)) != 0)
			{
				perror("Failed to create thread");
				return (-1);
			}
			i++;
		}
		i = 0;
		while (i < philo_nbr)
		{
			if (pthread_join(threads[i], NULL) != 0)
			{
				perror("Failed to terminate thread");
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
	/*
	if (finished/error)):
	clean + free.
	*/
	return (0);
}
