/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:55:37 by lraggio           #+#    #+#             */
/*   Updated: 2024/11/02 01:46:13 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_sim_status	check_simulation_status(t_philo *philo)
{
	t_sim_status	return_value;

	pthread_mutex_lock(philo->m_die_flag);
	return_value = *philo->die_flag;
	pthread_mutex_unlock(philo->m_die_flag);
	return (return_value);
}

t_sim_status	should_die_or_not(t_table *control, int i)
{
	t_sim_status	value;

	pthread_mutex_lock(&control->m_philo_last_meal[i]);
	value = (control->philo_last_meal[i] != 0 && (get_current_time(MILI)
				- control->philo_last_meal[i]) > control->die_time);
	pthread_mutex_unlock(&control->m_philo_last_meal[i]);
	return (value);
}

void	change_simulation_status(pthread_mutex_t *lock,
		t_sim_status *target_status, t_sim_status new_status)
{
	pthread_mutex_lock(lock);
	*target_status = new_status;
	pthread_mutex_unlock(lock);
	return ;
}

t_sim_status	check_observer_status(t_table *table)
{
	t_sim_status	observer_status;

	pthread_mutex_lock(&table->m_observer_status);
	observer_status = table->observer_status;
	pthread_mutex_unlock(&table->m_observer_status);
	return (observer_status);
}

void	*observer(void *ptr)
{
	t_table	*control;
	int		i;

	control = (t_table *)ptr;
	i = 0;
	while (42)
	{
		if (check_observer_status(control) == STOP)
			return (NULL);
		if (should_die_or_not(control, i) == STOP)
		{
			change_simulation_status(&control->m_die_flag, &control->die_flag,
				STOP);
			printf(RED "%ld philo %d is DEAD\n" RESET, get_current_time(MILI), i
				+ 1);
			return (NULL);
		}
		i++;
		if (i == control->nbr_philos)
			i = 0;
	}
	return (NULL);
}
