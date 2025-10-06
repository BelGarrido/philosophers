/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:49 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/06 13:38:21 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_locked(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->death_mutex);
	if (philo->data->philo_dead || philo->data->simulation_is_completed)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return ;
	}
	pthread_mutex_lock(philo->print_mutex);
	printf("%li %i %s\n", get_timestamp(philo->data->start_time),
		philo->id, msg);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->death_mutex);
}

/*time functions*/

long	get_time_ms(void)
{
	struct timeval	tv;
	long int		time;

	if (gettimeofday(&tv, NULL) != 0)
		perror("Error");
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	get_timestamp(long start_time)
{
	long long	time;

	time = get_time_ms() - start_time;
	return (time);
}

void	ft_usleep(long int miliseconds)
{
	long int		start;

	start = get_time_ms();
	while ((get_time_ms() - start) < miliseconds)
		usleep(100);
}
