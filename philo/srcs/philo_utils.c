/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:27:59 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/22 14:53:41 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	my_trylock(pthread_mutex_t *m_fork_state, int *fork_state)
{
	pthread_mutex_lock(m_fork_state);
	if (*fork_state == 0)
	{
		*fork_state = 1;
		pthread_mutex_unlock(m_fork_state);
		return (0);
	}
	pthread_mutex_unlock(m_fork_state);
	return (1);
}

