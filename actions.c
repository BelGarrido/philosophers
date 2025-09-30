#include "philo.h"

void eat(t_philo *philo)
{
		//proteger con mutex
	pthread_mutex_lock(&philo->data->monitor_mutex);
	philo->last_meal_time = get_time_ms();
	//philo->is_eating = 1;
	pthread_mutex_unlock(&philo->data->monitor_mutex);
	print_locked(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->monitor_mutex);
	philo->meals_count++;
	//philo->is_eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->data->monitor_mutex);

	//actiualizar comidas que ha comido el filosofo
	//actualizar last_meal_time
	//desbloquear los tenedores aqui?
	//hay que parar la simulación porque ya hayan comido todas las comidas o se haya muerto alguien?
}

void take_forks(t_philo *philo)
{

/* 	if(philo->id == 1)
    {
        pthread_mutex_lock(philo->l_fork);
        print_locked(philo, "has taken left fork");
        pthread_mutex_lock(philo->r_fork);
        print_locked(philo, "has taken right fork");
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        print_locked(philo, "has taken right fork");
        pthread_mutex_lock(philo->l_fork);
        print_locked(philo, "has taken left fork");
    } */
	if((philo->id % 2) == 0)
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
