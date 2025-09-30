#include "philo.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] != '\0' && str2[i] != '\0' && (i < n))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i < n)
	{
		return (str1[i] - str2[i]);
	}
	return (0);
}

void print_locked(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->death_mutex);
	if (philo->data->philo_dead || philo->data->simulation_is_completed)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return ;
	}
	if (ft_strncmp(msg, "died", 4) == 0)
	{
		philo->data->philo_dead = 1;
		pthread_mutex_lock(philo->print_mutex);
		printf("%li %i is dead\n", get_timestamp(philo->data->start_time),philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(philo->death_mutex);
		return;
	}
	pthread_mutex_lock(philo->print_mutex);
	printf("%li %i %s\n", get_timestamp(philo->data->start_time), philo->id, msg);	
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->death_mutex);
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