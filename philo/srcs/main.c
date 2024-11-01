/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:30:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/29 15:33:01 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include "../include/philo.h"

void create_philo_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        pthread_create(
            &table->threads[i], NULL, run_program, table->philosophers[i]);
        i++;
    }
    return;
}

void join_philo_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        pthread_join(table->threads[i], NULL);
        i++;
    }
    return;
}

/*
pthread_join: waits for the thread identified by thread to terminate. (If
that thread has already terminated, pthread_join() returns immediately.
*/

int main(int argc, char **argv)
{
    t_table table;
    pthread_t observer_thread;

    if (check_args(argc, argv))
        exit(EXIT_FAILURE);
    if (init_table(&table, argc, argv) != NO_ERROR)
        return (ERROR);
    if (pthread_create(&observer_thread, NULL, observer, &table) != 0)
        return (perror("Erro ao criar a thread do observador!\n"), ERROR);
    create_philo_threads(&table);
    join_philo_threads(&table);
    // para o observador e espera ele retornar antes de dar free em tudo
    stop_observer(&table.m_observer_status, &table.observer_status);
    pthread_join(observer_thread, NULL);
    final_clear(&table);
    return (NO_ERROR);
}

void    destroy_mutexes(t_table *table)
{
    int i;

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

void stop_observer(pthread_mutex_t *lock, t_sim_status *status)
{
    pthread_mutex_lock(lock);
    *status = STOP;
    pthread_mutex_unlock(lock);
}

void final_clear(t_table *table)
{
    int i;

    destroy_mutexes(table);
    i = 0;
    while (i < table->nbr_philos)
    {
        free(table->philosophers[i]);
        i++;
    }
    free(table->philosophers);

    free(table->philo_last_meal);
    free(table->m_fork_state);
    free(table->m_philo_last_meal);
    free(table->fork_state);
    free(table->threads);
}
