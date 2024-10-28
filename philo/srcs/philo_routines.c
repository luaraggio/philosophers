/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:10:46 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/27 23:37:48 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*run_program(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	update_last_meal(philo);
	while (42)
	{
		if (eat_routine(philo) == STOP)
			break ;
		if (think_routine(philo) == STOP)
			break ;
		if (sleep_routine(philo) == STOP)
			break ;
	}
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
}

void	update_last_meal(t_philo *philo) // Atualiza QUANDO começa a comer, não depois que comeu
{
	pthread_mutex_lock(philo->m_last_meal);
	*philo->last_meal = get_current_time(MICRO);
	pthread_mutex_unlock(philo->m_last_meal);
}

t_sim_status	eat_routine(t_philo *philo)
{
	if (philo->times_eaten == philo->max_eat)
		return (STOP);
	if (dinner_config(philo) == STOP)
		return (STOP);
	update_last_meal(philo);
	printf(GREEN "philo %d is eating\n" RESET, philo->philo_id);
	philo->times_eaten++;
	return_forks(philo);
	my_usleep(philo, philo->eat_time);
	return (CONTINUE);
}

int	sleep_routine(t_philo *philo)
{
	printf(BLUE "philo %d is sleeping\n" RESET, philo->philo_id);
	my_usleep(philo, philo->sleep_time);
	return (0);
}

int	think_routine(t_philo *philo)
{
	printf(YELLOW "philo %d is thinking\n" RESET, philo->philo_id);
	return (0);
}

int	dinner_config(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	// filósofos pares pegam o garfo direito primeiro
	{
		while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf(PINK "philo %d has taken right fork\n" RESET, philo->philo_id);
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf(PINK "philo %d has taken left fork\n" RESET, philo->philo_id);
	}
	else // filósofos ímpares pegam o garfo esquerdo primeiro
	{
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf(PINK "philo %d has taken left fork\n" RESET, philo->philo_id);
		while (my_trylock(philo->m_r_fork, philo->r_fork) != 0)
		{
			if (check_simulation_status(philo) == STOP)
				return (STOP);
		}
		printf(PINK "philo %d has taken right fork\n" RESET, philo->philo_id);
	}
	return (0);
}
