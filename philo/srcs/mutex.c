/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:27:59 by lraggio           #+#    #+#             */
/*   Updated: 2024/11/02 02:26:04 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*

camada anterior ao ato de pegar o garfo, pra saber se ele tá disponível ou não
-> assim, ele pode realizar outras ações s/ ficar preso na fila do mutex do
garfo!!!!

*/

/*int	my_trylock(pthread_mutex_t *m_fork_state, int *fork_state)
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
}*/

/**
 * @brief Tenta adquirir o bloqueio de um garfo e retorna seu estado.
 *
 * Esta função tenta bloquear um mutex associado ao estado de um garfo,
 * permitindo que um filósofo verifique se o garfo está disponível ou não.
 * Se o garfo estiver disponível, a função o marca como indisponível,
 * permitindo que outros filósofos saibam que ele não pode ser pego.
 *
 * @param m_fork_state Um ponteiro para o mutex que protege o estado do garfo.
 * @param fork_state Um ponteiro para a variável que armazena o estado do garfo:
 *                   1 - disponível; 0 - indisponível.
 *
 * @return int O estado do garfo antes de tentar bloqueá-lo:
 *             1 se o garfo estava disponível, 0 se estava indisponível.
 *
 * O garfo sempre termina como 1 nessa função, quer ele tenha entrado
 * como disponível, quer ele tenha entrado como indisponível.
 *
 * - O garfo é considerado indisponível após a execução da função.
 * - Esta função garante que apenas um filósofo possa alterar o estado do garfo
 *   de cada vez, evitando condições de corrida.
 */

int	my_trylock(pthread_mutex_t *m_fork_state, int *fork_state)
{
	int	return_value;

	pthread_mutex_lock(m_fork_state);
	return_value = *fork_state;
	*fork_state = 1;
	pthread_mutex_unlock(m_fork_state);
	return (return_value);
}

/*
 * Como estou alocando os mutexes de forma dinâmica, utilizo pthread_mutex_init.
 *
 * Caso fosse alocar de forma estática, deveria inicializar o mutex desta forma:
 *
 * pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 */

int	init_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->m_philo_last_meal[i], NULL) != 0)
			return (ERROR);
		if (pthread_mutex_init(table->m_fork_state, NULL) != 0)
			return (ERROR);
	}
	if (pthread_mutex_init(&table->m_die_flag, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&table->m_observer_status, NULL) != 0)
		return (ERROR);
	return (NO_ERROR);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->m_philo_last_meal[i]);
		pthread_mutex_destroy(&table->m_fork_state[i]);
		i++;
	}
	pthread_mutex_destroy(&table->m_die_flag);
	pthread_mutex_destroy(&table->m_observer_status);
}
