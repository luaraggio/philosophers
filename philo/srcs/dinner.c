/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:37:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/11/02 02:05:20 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->m_last_meal);
	*philo->last_meal = get_current_time(MILI);
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

t_sim_status	odd_try_forks(t_philo *philo) // par
{
	while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
	{
		if (check_simulation_status(philo) == STOP)
			return (STOP);
		usleep(100);
	}
	printf("%ld %d has taken a fork\n", get_current_time(MILI), \
		philo->philo_id);
	while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
	{
		if (check_simulation_status(philo) == STOP)
			return (STOP);
		usleep(100);
	}
	printf("%ld %d has taken a fork\n", get_current_time(MILI), \
		philo->philo_id);
	return (CONTINUE);
}

t_sim_status	even_try_forks(t_philo *philo) // ímpar
{
	while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
	{
		if (check_simulation_status(philo) == STOP)
			return (STOP);
		usleep(100);
	}
	printf("%ld %d has taken a fork\n", get_current_time(MILI), \
		philo->philo_id);
	while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
	{
		if (check_simulation_status(philo) == STOP)
			return (STOP);
		usleep(100);
	}
	printf("%ld %d has taken a fork\n", get_current_time(MILI), \
		philo->philo_id);
	return (CONTINUE);
}

t_sim_status	try_to_take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (odd_try_forks(philo) == STOP)
			return (STOP);
	}
	else
	{
		if (even_try_forks(philo) == STOP)
			return (STOP);
	}
	return (CONTINUE);
}
