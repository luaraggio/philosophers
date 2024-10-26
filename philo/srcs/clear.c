/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:10:17 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 20:22:46 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/*
 * 	A função final_clear é responsável por dar free em tudo que foi alocado.
 * Primeiro, destrói os mutexes. Em seguida, libera a struct s_philo usando
 * um loop que percorre toda a matriz de filósofos. Por fim, libera os arrays
 * da struct s_table.
 */

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_destroy(table->m_philo_last_meal);
		pthread_mutex_destroy(table->m_fork_state);
	}
}

void	final_clear(t_table *table)
{
	int	i;

	i = -1;
	destroy_mutexes(table);
	while (++i < table->nbr_philos)
		free(table->philosophers[i]);
	free(table->philosophers);
	free(table->philo_last_meal);
	free(table->fork_state);
	free(table->m_philo_last_meal);
	free(table->m_fork_state);
	free(table->threads);
	return ;
}
