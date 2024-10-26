/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:27:59 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 21:39:06 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	my_trylock(pthread_mutex_t *m_fork_state, int *fork_state)
/*camada anterior ao ato de pegar o garfo, pra saber se ele tá disponível ou não -> assim,
ele pode realizar outras ações s/ ficar preso na fila do mutex do garfo!!!!*/
{
	pthread_mutex_lock(m_fork_state); //locked p/ outros filósofos verem
	if (*fork_state == 0) //o garfo está disponível
	{
		*fork_state = 1; //peguei o garfo
		pthread_mutex_unlock(m_fork_state); //unlocked p/ outros filósofos verem
		return (0); //pegou o garfo
	}
	pthread_mutex_unlock(m_fork_state); //unlocked p/ outros filósofos verem
	return (1); //n pegou o garfo
}

