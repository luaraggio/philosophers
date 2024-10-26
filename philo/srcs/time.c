/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:29:55 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 20:44:29 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//inicializar start time!!!

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
}

int my_usleep(long time)
{
    long start_time;

    start_time = get_current_time();
    while (get_current_time() - start_time < time)
        usleep(100);
    return (0);
}

