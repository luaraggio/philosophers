/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:55:37 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/29 02:28:57 by lraggio          ###   ########.fr       */
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
		return (1);
	}
	pthread_mutex_unlock(&control->m_philo_last_meal[i]);
	return (0);
}

/*void	*observer(void *arg)
{
	t_table	*table = (t_table *)arg;
	int		i;

	while (1)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (should_die_or_not(table, i))
			{
				pthread_mutex_lock(&table->m_die_flag);
				table->die_flag = STOP;  // Sinaliza o fim da simulação
				pthread_mutex_unlock(&table->m_die_flag);
				printf(RED "Philosopher %d has died.\n" RESET, i + 1);
				return (NULL);  // Encerra a thread do observador
			}
			i++;
		}
	}
	return (NULL);
}*/

int	observer(t_table *control)
{
	int	i;

	i = 0;
	while (42)
	{
		if (should_die_or_not(control, i) != 0)//|| )has_philo_eated_enough(control, i))
		{
			pthread_mutex_lock(&control->m_die_flag);
			control->die_flag = STOP;
			printf("%ld philo %d is DEAD\n", get_time(1000), i + 1);
			pthread_mutex_unlock(&control->m_die_flag);
			return (DEAD);
		}
		i++;
		if (i == control->nbr_philos)
			i = 0;
		return (ALIVE);
	}
	return (ALIVE);
}
