/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:21:01 by lraggio           #+#    #+#             */
/*   Updated: 2024/11/02 01:58:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[31m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PINK "\033[35m"

typedef enum e_philo_status
{
	ALIVE,
	DEAD,
}				t_philo_status;

typedef enum e_ft_status
{
	NO_ERROR,
	ERROR,
}				t_ft_status;

typedef enum e_sim_status
{
	CONTINUE,
	STOP,
}				t_sim_status;

typedef enum e_time_precision
{
	MICRO = 1,
	MILI = 1000,
}				t_time_precision;

typedef struct s_table // control scruct
{
	int nbr_philos;
	int die_time;
	int eat_time;
	int sleep_time;
	int max_eat;
	t_sim_status die_flag;
	long *philo_last_meal; // to verify if a philo has died
	int *fork_state;
	t_sim_status observer_status;
	pthread_mutex_t *m_philo_last_meal;
	pthread_mutex_t *m_fork_state;
	pthread_mutex_t m_die_flag;
	pthread_t *threads;
	struct s_philo **philosophers;
	pthread_mutex_t m_observer_status;
}				t_table;

typedef struct s_philo // philosophers struct
{
	int philo_id;
	long *last_meal;
	int eat_time;
	int sleep_time;
	int max_eat;
	int times_eaten;
	t_sim_status *die_flag;
	int *l_fork;
	int *r_fork;
	pthread_mutex_t *m_last_meal;
	pthread_mutex_t *m_l_fork;
	pthread_mutex_t *m_r_fork;
	pthread_mutex_t *m_die_flag;
}				t_philo;

// --------------- Check Input -----------------
int				is_digit(int c);
int				is_in_range(char **argv);
int				is_nbr(char **argv);
int				check_args(int argc, char **argv);

// ---------------- Clean ----------------------
void			final_clear(t_table *table);

// --------------- Init Structs ----------------
int				init_table(t_table *table, int argc, char **argv);
void			init_philo_forks(t_philo *philo, int id, t_table *table);
struct s_philo	*create_philo(int id, t_table *table);

// --------------- Libft Utils -----------------
int				my_atoi(char *str);
long			is_negative(const char *str);
long			my_atol(const char *str);
void			my_bzero(void *s, size_t n);
void			*my_calloc(size_t nmemb, size_t size);

// ---------------- Main -----------------------
void			create_philo_threads(t_table *table);
void			join_philo_threads(t_table *table);
void			stop_observer(pthread_mutex_t *lock, t_sim_status *status);

// ---------------- Mutex ----------------------
int				my_trylock(pthread_mutex_t *m_fork_state, int *fork_state);
int				init_mutexes(t_table *table);
void			destroy_mutexes(t_table *table);

// ---------------- Philo Routines -------------
void			*run_program(void *ptr);
t_sim_status	eat_routine(t_philo *philo);
int				sleep_routine(t_philo *philo);
int				think_routine(t_philo *philo);
t_sim_status	try_to_take_forks(t_philo *philo);
void			update_last_meal(t_philo *philo);
void			set_last_meal(t_philo *philo, long time);
void			return_forks(t_philo *philo);
t_sim_status	odd_try_forks(t_philo *philo);
t_sim_status	even_try_forks(t_philo *philo);
t_sim_status	try_to_take_forks(t_philo *philo);

// ---------------- Status ---------------------
t_sim_status	check_simulation_status(t_philo *philo);
t_sim_status	should_die_or_not(t_table *control, int i);
void			*observer(void *ptr);
void			change_simulation_status(pthread_mutex_t *lock,
					t_sim_status *target_status, t_sim_status new_status);
t_sim_status	check_observer_status(t_table *table);

// ---------------- Time -----------------------
int				my_usleep(t_philo *philo, long time);
long			get_current_time(t_time_precision precision);

#endif
