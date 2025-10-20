/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:36 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/20 15:25:40 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* MONITORING ROUTINE*/

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (simulation_finished(data))
			return (NULL);
		if (any_philo_dead(data))
			return (NULL);
		if (check_if_all_ate(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			if (!data->philo_dead)
				data->simulation_is_completed = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		ft_usleep(1, data);
	}
	return (NULL);
}

/*PHILOSOPHER'S ROUTINE*/

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!simulation_finished(philo->data))
	{
		while (get_time_ms() < philo->data->start_time)
			usleep(100);
		pthread_mutex_lock(&philo->meals_mutex);
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&philo->meals_mutex);
		if (check_if_one_ate(philo))
			break ;
		if (take_forks(philo))
			eat(philo);
		if (check_if_one_ate(philo))
			break ;
		print_locked(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_locked(philo, "is thinking");
	}
	return (NULL);
}

		/* done = (philo->data->num_time_must_eat > 0
				&& philo->meals_count >= philo->data->num_time_must_eat);
		pthread_mutex_unlock(&philo->meals_mutex); 
		if (done)
			break; */