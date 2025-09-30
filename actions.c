#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->monitor_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->monitor_mutex);
	print_locked(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->monitor_mutex);
	philo->meals_count++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->data->monitor_mutex);
}

void	take_forks(t_philo *philo)
{
	if(philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);	
		print_locked(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		print_locked(philo, "died");
	}
	else if((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork"); //(right)
		pthread_mutex_lock(philo->l_fork);
		print_locked(philo, "has taken a fork"); //(left)
	}
	else if((philo->id % 2) != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_locked(philo, "has taken a fork"); //(left)
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork"); //(right)
	}
}
