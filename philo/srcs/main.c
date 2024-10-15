/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:30:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 02:31:14 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
input:

./philos  nbr_of_philos    time_to_die    time_to_eat    time_to_sleep   nbr_of_meals

example:

 ./philos 5 800 200 200 [5]
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

int	main(int argc, char **argv)
{
		t_table table;
		int i;

	if (check_args(argc, argv) == 0)
	{
		// start_program()!!!
		i = 0;
		init_table(&table, argc, argv);
		while (i < table.nbr_philos)
		{
			pthread_create(&table.threads[i], NULL, &teste,
				table.philosophers[i]);
			i++;
		}
		i = -1;
		while (++i < table.nbr_philos)
			pthread_join(table.threads[i], NULL);
	}
	else
	{
		// end_program()!!!!
		// free(no que foi mallocado);
		exit(EXIT_FAILURE);
	}
	// Limpar tudo ao final
}
