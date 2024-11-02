/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:17:15 by lraggio           #+#    #+#             */
/*   Updated: 2024/11/02 01:33:01 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 *	Essa primeira parte lida com a leitura e interpretação do input, ao veri-
 * ficar se os argumentos passados são válidos.
 *
 * number_of_philosophers: Número de filósofos e garfos.
 *
 * time_to_die: Tempo em milissegundos que um filósofo pode ficar sem comer
 * antes de morrer.
 *
 * time_to_eat: Tempo que um filósofo leva para comer.
 *
 * time_to_sleep: Tempo que um filósofo passa dormindo.
 *
 * number_of_times_each_philosopher_must_eat (input opcional): Número de vezes
 * que cada filósofo precisa comer antes da simulação parar.
 */

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_in_range(char **argv)
{
	long	j;

	j = 1;
	while (argv[j])
	{
		if (my_atol(argv[j]) > INT_MAX || argv[j] <= 0)
		{
			printf("Error: The input must be in the range: positives, \
			non-zero and less than MAX_INT numbers\n");
			return (1);
		}
		j++;
	}
	return (0);
}

int	is_nbr(char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] == '+')
				i++;
			if (!is_digit(argv[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
			printf("Invalid arguments.\nIt must be: ./philos  [nbr_of_philos] \
			[time_to_die]  [time_to_eat]  [time_to_sleep]  [nbr_of_meals]\n");
		return (ERROR);
	}
	if (is_nbr(argv) || is_in_range(argv))
		return (ERROR);
	return (NO_ERROR);
}
