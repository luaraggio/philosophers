
#include "../include/philo.h"

void	final_clear(t_table *table)
{
	int	i;

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
