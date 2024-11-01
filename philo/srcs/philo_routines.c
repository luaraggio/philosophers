/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:10:46 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/29 16:02:50 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*run_program(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	update_last_meal(philo);
	//printf("Philo %d started\n", philo->philo_id);
	while (42)
	{
		if (think_routine(philo) == STOP)
			break ;
		if (eat_routine(philo) == STOP)
			break ;
		if (sleep_routine(philo) == STOP)
			break ;

	}
	//printf("Philo %d stopped\n", philo->philo_id);
	return (NULL);
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

void	update_last_meal(t_philo *philo) // Atualiza QUANDO começa a comer, não depois que comeu
{
	pthread_mutex_lock(philo->m_last_meal);
	*philo->last_meal = get_current_time(MICRO);
	pthread_mutex_unlock(philo->m_last_meal);
	return ;
}

void	set_last_meal(t_philo *philo, long time)
{
	pthread_mutex_lock(philo->m_last_meal);
	*philo->last_meal = time;
	pthread_mutex_unlock(philo->m_last_meal);
	return ;
}

t_sim_status	eat_routine(t_philo *philo)
{
	update_last_meal(philo);
	printf(GREEN "%ld philo %d is eating\n" RESET, get_current_time(MILI),
		philo->philo_id);
	if (my_usleep(philo, philo->eat_time) == STOP)
		return (STOP);
	philo->times_eaten++;
	if (philo->times_eaten == philo->max_eat)
	{
		set_last_meal(philo, 0);
		return (STOP);
	}
	return_forks(philo);
	return (CONTINUE);
}

int	sleep_routine(t_philo *philo)
{
	printf(BLUE "%ld philo %d is sleeping\n" RESET, get_current_time(MILI),
		philo->philo_id);
	return my_usleep(philo, philo->sleep_time);
}

int	think_routine(t_philo *philo)
{
	printf(YELLOW "%ld philo %d is thinking\n" RESET, get_current_time(MILI),
		philo->philo_id);
	if (try_to_take_forks(philo) == STOP)
		return (STOP);
	return (CONTINUE);
}

int	try_to_take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf("philo %d has taken a fork\n", philo->philo_id);
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf("philo %d has taken a fork\n", philo->philo_id);
	}
	else
	{
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf("philo %d has taken a fork\n", philo->philo_id);
		while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf("philo %d has taken a fork\n", philo->philo_id);
	}
	return (CONTINUE);
}
