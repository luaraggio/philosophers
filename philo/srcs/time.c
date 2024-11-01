/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:29:55 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/29 15:33:41 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_current_time(t_time_precision precision)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1e6) + time.tv_usec) / precision);
}

int	my_usleep(t_philo *philo, long time)
{
	long	end;

	end = get_current_time(MICRO) + time;
	while (end > get_current_time(MICRO))
	{
		usleep(300);
		if (check_simulation_status(philo) == STOP) //checa se a simulação tem que acabar
			return (STOP);
	}
	return (CONTINUE);
}
