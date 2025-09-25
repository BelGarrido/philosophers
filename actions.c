#include "philo.h"

void eat(t_philo *philo)
{
	print_locked(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	//actiualizar comidas que ha comido el filosofo
	//actualizar last_meal_time
	//desbloquear los tenedores aqui?
	philo->meals_count++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
