/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:36 by anagarri          #+#    #+#             */
/*   Updated: 2025/09/30 17:54:55 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* MONITORING ROUTINE 🕵️*/

void	*monitor_routine(void *arg)
{
	t_data *data = (t_data*)arg;
	int philos_ate_enough = 0;
	int i;
	int time_since_meal;
	int meals_count;
	while(!data->philo_dead && !philos_ate_enough)
	{
		if(data->num_time_must_eat)
			philos_ate_enough = 1;
		i = 0;
		while(i < data->num_philos)
		{
			pthread_mutex_lock(&data->monitor_mutex);
			time_since_meal = get_time_ms() - data->philosophers[i].last_meal_time;
			meals_count = data->philosophers[i].meals_count;
			pthread_mutex_unlock(&data->monitor_mutex);
			if(time_since_meal > data->time_to_die)
			{
				print_locked(&data->philosophers[i], "died");
				return NULL;
			}
			if(meals_count < data->num_time_must_eat && data->num_time_must_eat != 0)
				philos_ate_enough = 0;
			i++;
		}
		usleep(500);
	}
	if(philos_ate_enough && data->num_time_must_eat)
	{
		pthread_mutex_lock(&data->death_mutex);
        data->simulation_is_completed = 1;
        pthread_mutex_unlock(&data->death_mutex);
		return NULL;
	}
	return NULL;
}

/*PHILOSOPHER'S ROUTINE 🧠*/

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	//printf("This is the function routine with philo[%i]\n", philo->id);
	while(!philo->data->philo_dead && !philo->data->simulation_is_completed)
	{
		take_forks(philo);
		eat(philo); //habra que cambiar algunas variables dentro 
		if(philo->data->num_time_must_eat && philo->meals_count >= philo->data->num_time_must_eat)
			break;
		print_locked(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_locked(philo, "is thinking");
		//printf("philo number %i, has eaten %i meals\n", philo->id, philo->meals_count);
	}
	return NULL;
}