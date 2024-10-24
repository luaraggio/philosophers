/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:10:46 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/23 23:31:43 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*is_philo_dead(t_table *control)
{

}*/

/*has_finished_eaten_times(t_table *control)
{

}*/

void	*end_program(t_table *control)
{
	if (is_philo_dead(control))
	{
		printf("Um filósofo morreu!\n");
		return (1);
	}
	if (has_finished_eaten_times(control))
	{
		printf("Todos os filósofos comeram o número de vezes necessário!\n");
		return (1);
	}
	return (0);
}

void    *all_routines(void *ptr)
{
	//eat_routine
	//sleep_routine
	//think_routine
}
