/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:22:05 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/20 15:22:11 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		pthread_mutex_destroy(&data->philosophers[i].meals_mutex);
		i++;
	}
	return (0);
}
