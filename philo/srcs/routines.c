/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:10:46 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/23 16:49:46 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void	*dinner_loop(t_table *control)
{
	while (42)
	{
		if (is_philo_dead(control) || has_finished_eaten_times(control))
		{
			printf("Loop do jantar foi interrompido!\n");
			break ;
		}
	}
	return (NULL);
}

/*is_philo_dead(t_table *control)
{

}

has_finished_eaten_times(t_table *control)
{
	
}*/

/*void    *all_routines(void *arg)
{
	//comer
	if (eat_routine() != 0)
		error;
	//dormir
	if (sleep_routine() != 0)
		error;
	//pensar
	if (think_routine() != 0)
		error;
	//morrer
}*/
