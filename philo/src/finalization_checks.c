/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalization_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:30:25 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/20 15:36:17 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* MONITORING ROUTINE 🕵️*/

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
	long	time_since_meal;

	if (check_if_one_ate(&data->philosophers[i]))
		return (0);
	pthread_mutex_lock(&data->philosophers[i].meals_mutex);
	time_since_meal = get_time_ms() - data->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&data->philosophers[i].meals_mutex);
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

int	check_if_one_ate(t_philo *philo)
{
	int	done;

	done = 0;
	pthread_mutex_lock(&philo->meals_mutex);
	done = (philo->data->num_time_must_eat > 0
			&& philo->meals_count >= philo->data->num_time_must_eat);
	pthread_mutex_unlock(&philo->meals_mutex);
	if (done)
		return (1);
	else
		return (0);
}

int	check_if_all_ate(t_data *data)
{
	int	i;
	int	meals_count;
	int	all_ate;

	if (data->num_time_must_eat == 0)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philosophers[i].meals_mutex);
		meals_count = data->philosophers[i].meals_count;
		pthread_mutex_unlock(&data->philosophers[i].meals_mutex);
		if (meals_count < data->num_time_must_eat)
			all_ate = 0;
		i++;
	}
	return (all_ate);
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
