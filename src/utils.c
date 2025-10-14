/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:49 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/14 18:37:30 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	join_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

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

void	ft_usleep(long time, t_data *data)
{
	long int		start;

	start = get_time_ms();
	while (!simulation_finished(data))
	{
		if ((get_time_ms() - start) < time)
			usleep(100);
		else
			break ;
	}
}
