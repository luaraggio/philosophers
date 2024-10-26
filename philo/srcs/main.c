/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:30:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 20:23:06 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
pthread_join: waits for the thread identified by thread to terminate. (If
that thread has already terminated, pthread_join() returns immediately.
*/

void	create_philos_thread(t_table *table, int i)
{
	while (i < table->nbr_philos)
	{
		pthread_create(&table->threads[i], NULL, run_program,
			table->philosophers[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_table	table;
	int	i;

	i = 0;
	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	init_table(&table, argc, argv);
	create_philos_thread(&table, i);
	i = -1;
	while (++i < table.nbr_philos)
		pthread_join(table.threads[i], NULL);
	//final_clear(&table);
	return (0);
}

