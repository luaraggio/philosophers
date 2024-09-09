#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

typedef struct	s_table
{
    int                 nbr_philos;
    int                 die_time;
    int                 eat_time;
    int                 sleep_time;
    int                 max_eat;
    long                start_time; // to verify when the simulation begins
    bool                end_simulation;
    long                *philo_last_meal; //to verify if the philo has died
    int                 *fork_state;
    pthread_mutex_t     *m_philo_last_meal;
    pthread_mutex_t     *m_fork_state;
    pthread_t           *threads;
    struct s_philo      **philosophers;
}   t_table;

typedef struct	s_philo
{
    int                 philo_id;
    long                *last_meal;
    pthread_mutex_t     *m_last_meal;
    int                 die_time;
    int                 eat_time;
    int                 sleep_time;
    int                 max_eat;
    int                 times_eaten;
    int                 *l_fork;
    int                 *r_fork;
    pthread_mutex_t     *m_l_fork;
    pthread_mutex_t     *m_r_fork;
}   t_philo;

//Philo functions
int             ft_trylock(pthread_mutex_t *m_fork_state, int *fork_state);
int             init_table(t_table *table, int argc, char **argv);
struct s_philo  *create_philo(int id, t_table *table);
long unsigned   get_time(void);


void            *ft_calloc(size_t nmemb, size_t size);
void            ft_bzero(void *s, size_t n);
int             ft_atoi(char *str);
int             is_in_range(char **argv);
int             is_nbr(char **argv);
int     check_args(int argc, char **argv);
int             is_digit(int c);
long	        is_negative(const char *str);
long	        ft_atol(const char *str);


#endif
