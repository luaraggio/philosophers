/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:55:37 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/30 00:18:44 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	should_die_or_not(t_table *control, int i)
{
	pthread_mutex_lock(&control->m_philo_last_meal[i]);
	if (control->philo_last_meal[i] != -1 && (get_current_time(MICRO)
			- control->philo_last_meal[i]) >= control->die_time)
	{
		pthread_mutex_unlock(&control->m_philo_last_meal[i]);
		return (DIE);
	}
	pthread_mutex_unlock(&control->m_philo_last_meal[i]);
	return (LIVE);
}

/*int	observer(t_table *control)
{
	int	i;

	i = 0;
	while (42)
	{

		if (should_die_or_not(control, i) == DIE)
		{
			pthread_mutex_lock(&control->m_die_flag);
			control->die_flag = STOP;
			printf(RED"%ld philo %d is DEAD\n"RESET, get_current_time(1000), i + 1);
			pthread_mutex_unlock(&control->m_die_flag);
			return (DEAD);
		}
		i++;
		if (i == control->nbr_philos)
			i = 0;
		return (ALIVE);
	}
	return (ALIVE);
}*/

void* observer(void* arg)
{
	int	i;
	t_table *control;

	i = 0;
	control = (t_table *)arg;
	while (42)
	{

		if (should_die_or_not(control, i) == DIE)
		{
			pthread_mutex_lock(&control->m_die_flag);
			control->die_flag = STOP;
			printf(RED"%ld philo %d is DEAD\n"RESET, get_current_time(1000), i + 1);
			pthread_mutex_unlock(&control->m_die_flag);
			break ;
		}
		i++;
		if (i == control->nbr_philos)
			i = 0;
		return (NULL);
	}
	return (NULL);
}
