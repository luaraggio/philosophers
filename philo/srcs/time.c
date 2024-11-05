
#include "../include/philo.h"

long	get_current_time(t_time_precision precision)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1e6) + time.tv_usec) / precision);
}

int	my_usleep(t_philo *philo, long time)
{
	long	end;

	end = get_current_time(MICRO) + time;
	while (end > get_current_time(MICRO))
	{
		usleep(100);
		if (check_simulation_status(philo) == STOP)
			return (STOP);
	}
	return (CONTINUE);
}
