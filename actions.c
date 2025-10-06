/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:26:11 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/06 12:48:17 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_unlock(&philo->data->monitor_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);

}

void	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_lock(&philo->data->death_mutex);
        if (!philo->data->philo_dead && !philo->data->simulation_is_completed)
        {
            philo->data->philo_dead = 1;
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("%li %i died\n",
                get_timestamp(philo->data->start_time), philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
        pthread_mutex_unlock(philo->r_fork);
        return ;
	}
	else if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_locked(philo, "has taken a fork");
	}
	else if ((philo->id % 2) != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_locked(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork");
	}
}

int	close_simulation(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->monitor_mutex);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}
