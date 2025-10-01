/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:36 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/01 17:12:22 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* MONITORING ROUTINE 🕵️*/

static int	philo_is_dead(t_data *data, int i)
{
	int	time_since_meal;

	pthread_mutex_lock(&data->monitor_mutex);
	time_since_meal = get_time_ms() - data->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&data->monitor_mutex);
	if (time_since_meal > data->time_to_die)
	{
		print_locked(&data->philosophers[i], "died");
		return (1);
	}
	return (0);
}

static int	check_if_all_ate(t_data *data)
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

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->philo_dead)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (philo_is_dead(data, i))
				return (NULL);
			i++;
		}
		if (check_if_all_ate(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->simulation_is_completed = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

/*PHILOSOPHER'S ROUTINE 🧠*/

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		should_continue;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		should_continue = !philo->data->philo_dead
			&& !philo->data->simulation_is_completed;
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (!should_continue)
			break ;
		take_forks(philo);
		eat(philo);
		print_locked(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_locked(philo, "is thinking");
	}
	return (NULL);
}
