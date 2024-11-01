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
    if (pthread_create(&observer_thread, NULL, observer, &table) != 0
        || pthread_detach(observer_thread) != 0)
        return (perror("Erro ao criar a thread do observador!\n"), ERROR);
    create_philo_threads(&table);
    join_philo_threads(&table);
    final_clear(&table);
    return (NO_ERROR);
}

void final_clear(t_table *table)
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

    i = 0;
    while (i < table->nbr_philos)
    {
        free(table->philosophers[i]);
        i++;
    }

    free(table->philosophers);
    free(table->m_fork_state);
    free(table->m_philo_last_meal);
    free(table->fork_state);
    free(table->threads);
}
