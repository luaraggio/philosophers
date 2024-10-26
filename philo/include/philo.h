/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:21:01 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 21:27:02 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[31m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PINK "\033[35m"

typedef struct s_table // control scructure
{
	int nbr_philos;
	int die_time;
	int eat_time;
	int sleep_time;
	int max_eat;
	long start_time; // to verify when the simulation begins
	long *philo_last_meal; // to verify if a philo has died
	int *fork_state;
	pthread_mutex_t *m_philo_last_meal;
	pthread_mutex_t *m_fork_state;
	pthread_t *threads;
	struct s_philo **philosophers;
}				t_table;

typedef struct s_philo // philosophers structure
{
	int philo_id;
	long *last_meal;
	pthread_mutex_t *m_last_meal;
	int die_time;
	int eat_time;
	int sleep_time;
	int max_eat;
	int times_eaten;
	int *l_fork;
	int *r_fork;
	pthread_mutex_t *m_l_fork;
	pthread_mutex_t *m_r_fork;
}				t_philo;

struct s_philo	*create_philo(int id, t_table *table);

int				my_usleep(long time);
int				my_trylock(pthread_mutex_t *m_fork_state, int *fork_state);
int				init_table(t_table *table, int argc, char **argv);
int				my_atoi(char *str);
int				is_in_range(char **argv);
int				is_nbr(char **argv);
int				check_args(int argc, char **argv);
int				is_digit(int c);
int				eat_routine(t_philo *philo);
int				sleep_routine(t_philo *philo);
int				think_routine(t_philo *philo);

void			*run_program(void *ptr);
void			*my_calloc(size_t nmemb, size_t size);
void			my_bzero(void *s, size_t n);
void			my_putchar_fd(char c, int fd);

long			get_current_time(void);
long			is_negative(const char *str);
long			my_atol(const char *str);

#endif
