
#include "../include/philo.h"

void	*run_program(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	update_last_meal(philo);
	while (42)
	{
		if (think_routine(philo) == STOP || eat_routine(philo) == STOP
			|| sleep_routine(philo) == STOP)
			break ;
	}
	return (NULL);
}

t_sim_status	eat_routine(t_philo *philo)
{
	update_last_meal(philo);
	printf(GREEN "%ld %d is eating\n" RESET, get_current_time(MILI),
		philo->philo_id);
	if (my_usleep(philo, philo->eat_time * 1e3) == STOP)
		return (STOP);
	philo->times_eaten++;
	return_forks(philo);
	if (philo->times_eaten == philo->max_eat)
	{
		set_last_meal(philo, 0);
		return (STOP);
	}
	return (CONTINUE);
}

void	return_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->m_r_fork);
		*philo->r_fork = 0;
		pthread_mutex_unlock(philo->m_r_fork);
		pthread_mutex_lock(philo->m_l_fork);
		*philo->l_fork = 0;
		pthread_mutex_unlock(philo->m_l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->m_l_fork);
		*philo->l_fork = 0;
		pthread_mutex_unlock(philo->m_l_fork);
		pthread_mutex_lock(philo->m_r_fork);
		*philo->r_fork = 0;
		pthread_mutex_unlock(philo->m_r_fork);
	}
	return ;
}

int	sleep_routine(t_philo *philo)
{
	printf(BLUE"%ld %d is sleeping\n"RESET, get_current_time(MILI),
		philo->philo_id);
	return (my_usleep(philo, philo->sleep_time * 1e3));
}

int	think_routine(t_philo *philo)
{
	printf(YELLOW"%ld %d is thinking\n"RESET, get_current_time(MILI),
		philo->philo_id);
	return (try_to_take_forks(philo));
}
