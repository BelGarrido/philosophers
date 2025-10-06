/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalization_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:30:25 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/06 13:39:35 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* MONITORING ROUTINE 🕵️*/

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

int	simulation_finished(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->simulation_is_completed == 1 || data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

static int	philo_is_dead(t_data *data, int i)
{
	long	ts;
	int		time_since_meal;

	pthread_mutex_lock(&data->monitor_mutex);
	time_since_meal = get_time_ms() - data->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&data->monitor_mutex);
	if (time_since_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->philo_dead && !data->simulation_is_completed)
		{
			data->philo_dead = 1;
			ts = get_timestamp(data->start_time);
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%li %d died\n", ts, data->philosophers[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

int	check_if_all_ate(t_data *data)
{
	int	i;
	int	meals_count;

	if (data->num_time_must_eat == 0)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->monitor_mutex);
		meals_count = data->philosophers[i].meals_count;
		pthread_mutex_unlock(&data->monitor_mutex);
		if (meals_count < data->num_time_must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	any_philo_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (philo_is_dead(data, i))
			return (1);
		i++;
	}
	return (0);
}
