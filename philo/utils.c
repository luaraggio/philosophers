#include "philo.h"

int     ft_trylock(pthread_mutex_t *m_fork_state, int *fork_state)
{
    pthread_mutex_lock(m_fork_state);
    if (*fork_state == 0)
    {
        *fork_state = 1;
        pthread_mutex_unlock(m_fork_state);
        return (0);
    }
    pthread_mutex_unlock(m_fork_state);
    return (1);
}

void	ft_bzero(void *s, size_t n)
{
	char	*a;

	a = (char *) s;
	while (n > 0)
	{
		a[n - 1] = '\0';
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if ((nmemb) && (size * nmemb > 0) && ((nmemb * size) / nmemb != size))
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, (nmemb * size));
	return (str);
}

long unsigned   get_time(void)
{
    return (1);
}