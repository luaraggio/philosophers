#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct	s_sets
{

}		t_sets;

typedef struct	s_philo
{
    pthread_mutex_t     *mutex;
    struct s_philo      **philosophers;
    int     philo_id;
    int     *forks;
    int     *l_fork;
    int     *r_fork;
}		t_philo;

#endif
