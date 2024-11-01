/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:55:37 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/29 15:41:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include "../include/philo.h"

t_sim_status	check_simulation_status(t_philo *philo)
{
	pthread_mutex_lock(philo->m_die_flag);
	if (*philo->die_flag == STOP)
	{
		pthread_mutex_unlock(philo->m_die_flag);
		return (STOP);
	}
	pthread_mutex_unlock(philo->m_die_flag);
	return (CONTINUE);
}

t_sim_status should_die_or_not(t_table *control, int i)
{
	pthread_mutex_lock(&control->m_philo_last_meal[i]);
	if (control->philo_last_meal[i] != 0 && (get_current_time(MICRO)
			- control->philo_last_meal[i]) > control->die_time)
	{
		pthread_mutex_unlock(&control->m_philo_last_meal[i]);
		return (STOP);
	}
	pthread_mutex_unlock(&control->m_philo_last_meal[i]);
	return (CONTINUE);
}

void	change_simulation_status(pthread_mutex_t *lock,  t_sim_status *target_status, t_sim_status new_status) {

	pthread_mutex_lock(lock);
	*target_status = new_status;
	pthread_mutex_unlock(lock);
	return ;
}

void	*observer(void *ptr)
{
	t_table *control;
	int	i;

	control = (t_table *)ptr;
	i = 0;
	while (42)
	{

		if (should_die_or_not(control, i) == STOP)
		{
			change_simulation_status(&control->m_die_flag, &control->die_flag, STOP);
			printf("%ld philo %d is DEAD\n", get_current_time(MILI), i + 1);
			return (NULL);
		}
		i++;
		if (i == control->nbr_philos)
			i = 0;
	}
	return (NULL);
}
