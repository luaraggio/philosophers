#include "philo.h"

int     init_table(t_table *table, int argc, char **argv)
{
    int     i;

    i = 0;
    table->nbr_philos = ft_atoi(argv[1]);
    table->die_time = ft_atoi(argv[2]);
    table->eat_time = ft_atoi(argv[3]);
    table->sleep_time = ft_atoi(argv[4]);
    if (argc == 6)
        table->max_eat = ft_atoi(argv[5]);
    else
        table->max_eat = -1;
    table->philo_last_meal = ft_calloc(sizeof(long), (table->nbr_philos + 1));
    table->fork_state = ft_calloc(sizeof(int), (table->nbr_philos + 1));
    table->m_philo_last_meal = ft_calloc(sizeof(pthread_mutex_t), (table->nbr_philos + 1));
    table->m_fork_state = ft_calloc(sizeof(pthread_mutex_t), (table->nbr_philos + 1));
    table->threads = ft_calloc(sizeof(pthread_t), (table->nbr_philos + 1));
    if (!table->philo_last_meal || !table->fork_state 
        || !table->m_philo_last_meal || !table->m_fork_state || !table->threads)
            return (1);
    while (i < table->nbr_philos)
    {
        table->philosophers[i] = create_philo(i + 1, table);
        if (!table->philosophers[i])
            return (1);
        i++;
    }
    return (0);
}

struct s_philo  *create_philo(int id, t_table *table)
{
    struct s_philo *philo;

    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (NULL);
    philo->philo_id = id;
    philo->last_meal = &table->philo_last_meal[id - 1];
    philo->m_last_meal = &table->m_philo_last_meal[id - 1];
    philo->sleep_time = table->sleep_time;
    philo->eat_time = table->eat_time;
    philo->die_time = table->die_time;
    philo->times_eaten = 0;
    philo->l_fork = &table->fork_state[id - 1];
    philo->m_l_fork = &table->m_fork_state[id - 1];
    if (id == table->nbr_philos)
    {
        philo->m_r_fork = &table->m_fork_state[0];
        philo->r_fork = &table->fork_state[0];
    }
    else
    {
        philo->m_r_fork = &table->m_fork_state[id];
        philo->r_fork = &table->fork_state[id];
    }
    philo->max_eat = table->max_eat;
    return (philo);
}