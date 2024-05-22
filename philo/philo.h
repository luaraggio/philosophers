#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef struct	s_sets
{
    pthread_mutex_t     *l_forks;
    pthread_mutex_t     *r_forks;
    int     number_philos;
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

int     ft_atoi(char *str);
int     ft_isdigit(int c);
long    ft_atol(char *str);

#endif
