#include "philo.h"

void    *teste(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    printf("---------------------\nid: %d\nl_fork: %p\nr_fork: %p\nmax_eat: %d\ntimes_eaten: %d\neat_time: %d\ndie_time: %d\nsleep_time: %d\n-----------------\n", philo->philo_id, philo->l_fork, philo->r_fork, philo->max_eat, philo->times_eaten, philo->eat_time, philo->die_time, philo->sleep_time);
    return (NULL);
}

int     main(int argc, char **argv)
{
    t_table     table;
    int         i;
    
    i = 0;
    init_table(&table, argc, argv);
    while(i < table.nbr_philos)
    {
        pthread_create(&table.threads[i], NULL, &teste, table.philosophers[i]);
        i++;
    }
    i = 0;
    while(i < table.nbr_philos)
    {
        pthread_join(table.threads[i], NULL);
        i++;
    }
}