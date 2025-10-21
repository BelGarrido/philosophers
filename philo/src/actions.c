/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:26:11 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/20 15:20:30 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meals_mutex);
	print_locked(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->meals_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->data->num_time_must_eat > 0 && check_if_all_ate(philo->data))
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->simulation_is_completed = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
}

void	one_filosopher_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_locked(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	if (!simulation_finished(philo->data))
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->philo_dead = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%li %i died\n",
			get_timestamp(philo->data->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(philo->r_fork);
}

int	fork_is_taken(pthread_mutex_t *first, pthread_mutex_t *second,
		t_philo *philo)
{
	pthread_mutex_lock(first);
	print_locked(philo, "has taken a fork");
	if (simulation_finished(philo->data))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	print_locked(philo, "has taken a fork");
	if (simulation_finished(philo->data))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		one_filosopher_routine(philo);
		return (0);
	}
	if (simulation_finished(philo->data))
		return (0);
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (philo->r_fork < philo->l_fork)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	if (!fork_is_taken(first_fork, second_fork, philo))
		return (0);
	return (1);
}

/* void	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		return (one_filosopher_routine(philo));
	}
	if (simulation_finished(philo->data))
		return ;
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_locked(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_locked(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_locked(philo, "has taken a fork");
	}
} */
