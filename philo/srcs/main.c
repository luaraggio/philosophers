/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:30:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/27 18:55:27 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_create(&table->threads[i], NULL, run_program,
			table->philosophers[i]);
		i++;
	}
	return ;
}

void	join_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
	return ;
}

/*
pthread_join: waits for the thread identified by thread to terminate. (If
that thread has already terminated, pthread_join() returns immediately.
*/

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	if (init_table(&table, argc, argv) != NO_ERROR)
		return (ERROR);
	create_philo_threads(&table);
	observer(&table);
	join_philo_threads(&table);
	// final_clear(&table);
	// destroy_mutexes(&table);
	return (NO_ERROR);
}
