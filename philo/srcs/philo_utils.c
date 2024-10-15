/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:27:59 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 02:32:46 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_trylock(pthread_mutex_t *m_fork_state, int *fork_state)
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

long unsigned	get_time(void)
{
	return (1);
}
