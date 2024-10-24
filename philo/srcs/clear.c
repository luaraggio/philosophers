/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:10:17 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/24 00:10:01 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
