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
		if (eat_routine(philo) == STOP)
			break ;
		if (sleep_routine(philo) == STOP)
			break ;
		if (think_routine(philo) == STOP)
			break ;

	}
	//printf("Philo %d stopped\n", philo->philo_id);
	return (NULL);
}

void	return_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->m_l_fork);
	*philo->l_fork = 0;
	pthread_mutex_unlock(philo->m_l_fork);
	pthread_mutex_lock(philo->m_r_fork);
	*philo->r_fork = 0;
	pthread_mutex_unlock(philo->m_r_fork);
	return ;
}

void	update_last_meal(t_philo *philo) // Atualiza QUANDO começa a comer, não depois que comeu
{
	pthread_mutex_lock(philo->m_last_meal);
	*philo->last_meal = get_current_time(MICRO);
	pthread_mutex_unlock(philo->m_last_meal);
	return ;
}

t_sim_status	eat_routine(t_philo *philo)
{
	if (*philo->times_eaten == philo->max_eat)
		return (STOP);
	if (dinner_config(philo) == STOP)
		return (STOP);
	update_last_meal(philo);
	printf(GREEN "%ld philo %d is eating\n" RESET, get_current_time(1000),
		philo->philo_id);
	pthread_mutex_lock(philo->m_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->m_times_eaten);
	return_forks(philo);
	my_usleep(philo, philo->eat_time);
	return (CONTINUE);
}

int	sleep_routine(t_philo *philo)
{
	printf(BLUE "%ld philo %d is sleeping\n" RESET, get_current_time(1000),
		philo->philo_id);
	my_usleep(philo, philo->sleep_time);
	return (CONTINUE);
}

int	think_routine(t_philo *philo)
{
	printf(YELLOW "%ld philo %d is sleeping\n" RESET, get_current_time(1000),
		philo->philo_id);
	return (CONTINUE);
}

int	dinner_config(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		//printf("philo %d has taken right fork\n", philo->philo_id);
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		//printf("philo %d has taken left fork\n", philo->philo_id);
	}
	else
	{
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		//printf("philo %d has taken left fork\n", philo->philo_id);
		while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		//printf("philo %d has taken right fork\n", philo->philo_id);
	}
	return (CONTINUE);
}
