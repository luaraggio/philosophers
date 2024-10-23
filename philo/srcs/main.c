/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:30:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/23 16:23:06 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
input:

./philos  nbr_of_philos    time_to_die    time_to_eat    time_to_sleep   nbr_of_meals

ex.

 ./philos 3 800 200 200 5
*/

void	*teste(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	printf("---------------------\n");
	printf("id: %d\n", philo->philo_id);
	printf("l_fork: %p\n", philo->l_fork);
	printf("r_fork: %p\n", philo->r_fork);
	printf("max_eat: %d\n", philo->max_eat);
	printf("times_eaten: %d\n", philo->times_eaten);
	printf("eat_time: %d\n", philo->eat_time);
	printf("die_time: %d\n", philo->die_time);
	printf("sleep_time: %d\n", philo->sleep_time);
	printf("---------------------\n");
	return (NULL);
}

void	start_program(t_table *table, int i)
{
	while (i < table->nbr_philos)
	{
		pthread_create(&table->threads[i], NULL, &dinner_loop,
			table->philosophers[i]);
		i++;
	}
	return ;
}

/*
 * 	A função final_clear é responsável por dar free em tudo que foi alocado.
 * Primeiro, destrói os mutexes. Em seguida, libera a struct s_philo usando
 * um loop que percorre toda a matriz de filósofos. Por fim, libera os arrays
 * da struct s_table.
*/

void	final_clear(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_destroy(table->m_philo_last_meal);
		pthread_mutex_destroy(table->m_fork_state);
	}
	i = -1;
	while (++i < table->nbr_philos)
		free(table->philosophers[i]);
	free(table->philo_last_meal);
	free(table->fork_state);
	free(table->m_philo_last_meal);
	free(table->m_fork_state);
	free(table->threads);
	free(table->philosophers);
	return ;
}

/*
pthread_join: waits for the thread identified by thread to terminate. (If
that thread has already terminated, pthread_join() returns immediately.
*/

int	main(int argc, char **argv)
{
		t_table table;
		int i;

	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	i = 0;
	init_table(&table, argc, argv);
	start_program(&table, i);
	i = -1;
	while (++i < table.nbr_philos)
		pthread_join(table.threads[i], NULL);
	final_clear(&table);
	return (0);
}
