/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:17:17 by lraggio           #+#    #+#             */
/*   Updated: 2024/11/02 02:26:33 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	i = -1;
	table->nbr_philos = my_atol(argv[1]);
	table->die_time = my_atol(argv[2]);
	table->eat_time = my_atol(argv[3]);
	table->sleep_time = my_atol(argv[4]);
	if (argc == 6)
		table->max_eat = my_atol(argv[5]);
	else
		table->max_eat = -1;
	if (allocate_resources(table) == ERROR)
		return (ERROR);
	init_mutexes(table);
	while (++i < table->nbr_philos)
	{
		table->philosophers[i] = create_philo(i + 1, table);
		if (!table->philosophers[i])
			return (ERROR);
	}
	table->die_flag = CONTINUE;
	table->observer_status = CONTINUE;
	return (NO_ERROR);
}

int	allocate_resources(t_table *table)
{
	table->philo_last_meal = my_calloc(sizeof(long), (table->nbr_philos + 1));
	table->fork_state = my_calloc(sizeof(int), (table->nbr_philos + 1));
	table->m_philo_last_meal = my_calloc(sizeof(pthread_mutex_t),
			(table->nbr_philos + 1));
	table->m_fork_state = my_calloc(sizeof(pthread_mutex_t), (table->nbr_philos
				+ 1));
	table->threads = my_calloc(sizeof(pthread_t), (table->nbr_philos + 1));
	table->philosophers = my_calloc(sizeof(struct s_philo *), table->nbr_philos
			+ 1);
	if (!table->philo_last_meal || !table->fork_state
		|| !table->m_philo_last_meal || !table->m_fork_state || !table->threads
		|| !table->philosophers)
		return (ERROR);
	return (NO_ERROR);
}

void	init_philo_forks(t_philo *philo, int id, t_table *table)
{
	philo->l_fork = &table->fork_state[id - 1];
	philo->m_l_fork = &table->m_fork_state[id - 1];
	if (id == table->nbr_philos)
	{
		philo->m_r_fork = &table->m_fork_state[0];
		philo->r_fork = &table->fork_state[0];
	}
	else
	{
		philo->m_r_fork = &table->m_fork_state[id];
		philo->r_fork = &table->fork_state[id];
	}
	return ;
}

struct s_philo	*create_philo(int id, t_table *table)
{
	struct s_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = id;
	philo->last_meal = &table->philo_last_meal[id - 1];
	philo->m_last_meal = &table->m_philo_last_meal[id - 1];
	philo->sleep_time = table->sleep_time;
	philo->eat_time = table->eat_time;
	philo->die_flag = &table->die_flag;
	philo->m_die_flag = &table->m_die_flag;
	philo->max_eat = table->max_eat;
	init_philo_forks(philo, id, table);
	return (philo);
}
