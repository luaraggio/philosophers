/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:10:46 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 23:01:09 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	if (end_program(control))
		//os filósofos não devem verificar a própria morte!!
	{
		printf("Loop foi interrompido por morte/ fim do número de refeições!\n");
		break ;
	}
*/

void	dinner_config(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
			//ver se a simulação deve acabar ou não
		printf(PINK"philo %d has taken left fork\n"RESET, philo->philo_id);
		my_trylock(philo->m_r_fork, philo->r_fork);
		printf(PINK"philo %d has taken right fork\n"RESET, philo->philo_id);
		printf("Filósofo par pegou os dois garfos\n");
	}
	else
	{
		while (my_trylock(philo->m_l_fork, philo->l_fork) != 0)
			//ver se a simulação deve acabar ou não
		my_trylock(philo->m_l_fork, philo->l_fork);
		printf(PINK"philo %d has taken left fork\n"RESET, philo->philo_id);
		my_trylock(philo->m_r_fork, philo->r_fork);
		printf(PINK"philo %d has taken right fork\n"RESET, philo->philo_id);
		printf("Filósofo ímpar pegou os dois garfos\n");
	}
}

void	*run_program(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (42)
	{
		if (eat_routine(philo) != 0)
			break ;
		if (think_routine(philo) != 0) //tentando comer
			break ;
		if (sleep_routine(philo) != 0) //dormir pelas metades p/ verificar se morreu nesse meio tempo
			break ;
	}
	return (NULL);
}

int	eat_routine(t_philo *philo)
{
	if (philo->times_eaten == philo->max_eat)
		return (1);
	dinner_config(philo);
	philo->eat_time = get_current_time();
	printf(GREEN"philo %d is eating\n" RESET, philo->philo_id); // comer
	philo->times_eaten++;
	my_usleep(philo->eat_time);
	return (0);
}

int	sleep_routine(t_philo *philo)
{
	philo->sleep_time = get_current_time();
	printf(BLUE"philo %d is sleeping\n" RESET, philo->philo_id); // dormir
	my_usleep(philo->sleep_time);
	return (0);
}

int	think_routine(t_philo *philo)
{
	printf(YELLOW"philo %d is thinking\n" RESET, philo->philo_id); // pensar
	return (0);
}

/*must_die_or_not(t_table *control)
{
	printf(RED"philo %d is DEAD.\n"RESET, philo->philo_id); // morreu
}*/

/*has_finished_eaten_times(t_table *control)
{

}*/

/*void	*end_program(t_table *control)
{
	if (must_die_or_not(control))
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
}*/
