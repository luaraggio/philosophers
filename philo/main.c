#include "philo.h"

/*
input:./philos  nbr_of_philos    time_to_die    time_to_eat    time_to_sleep   nbr_of_meals

example: ./philos 5 800 200 200 [5]
*/

void    *teste(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    printf("---------------------\nid: %d\nl_fork: %p\nr_fork: %p\nmax_eat: %d\ntimes_eaten: %d\neat_time: %d\ndie_time: %d\nsleep_time: %d\n-----------------\n", philo->philo_id, philo->l_fork, philo->r_fork, philo->max_eat, philo->times_eaten, philo->eat_time, philo->die_time, philo->sleep_time);
    return (NULL);
}

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

int     main(int argc, char **argv)
{
    t_table     table;
    int         i;

    i = 0;
    if (check_args(argc, argv) == 0)
    {
        init_table(&table, argc, argv);
        while(i < table.nbr_philos)
        {
            pthread_create(&table.threads[i], NULL, &teste, table.philosophers[i]);
            i++;
        }
        i = -1;
        while(++i < table.nbr_philos)
            pthread_join(table.threads[i], NULL);
    //dinner_start(&table);
    }
    else
    {
        //free(no que foi mallocado);
        exit(EXIT_FAILURE);
    }
    //Limpar tudo ao final
}
