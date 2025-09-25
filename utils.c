#include "philo.h"


void print_locked(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%li %i %s\n", get_timestamp(philo->data->start_time),philo->id, msg);
	pthread_mutex_unlock(philo->print_mutex);

}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}