/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:03:25 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/14 18:37:59 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			perror("Error");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philosophers(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_count = 0;
		philo[i].last_meal_time = get_time_ms();
		philo[i].data = data;
		philo[i].r_fork = &data->forks[i];
		philo[i].l_fork = &data->forks[(i + 1) % data->num_philos];
		philo[i].print_mutex = &data->print_mutex;
		philo[i].death_mutex = &data->death_mutex;
		pthread_mutex_init(&philo[i].meals_mutex, NULL);
		i++;
	}
	return (1);
}

int	start_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine,
				(void *)&philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_data(t_data *data, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_time_must_eat = ft_atoi(argv[5]);
	else
		data->num_time_must_eat = 0;
	data->simulation_is_completed = 0;
	data->philo_dead = 0;
	data->start_time = get_time_ms() + 100;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->monitor_mutex, NULL);
	data->philosophers = NULL;
	data->forks = NULL;
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			philo[MAX];
	pthread_mutex_t	forks[MAX];

	if (!check_valid_argument(argv, argc))
		return (1);
	init_data(&data, argv);
	data.philosophers = philo;
	data.forks = forks;
	if (!init_forks(forks, &data))
		return (1);
	if (!init_philosophers(philo, &data))
		return (1);
	if (!start_threads(philo, &data))
		return (1);
	if (pthread_create(&data.monitor_thread, NULL, monitor_routine,
			(void *)&data) != 0)
		return (1);
	if (pthread_join(data.monitor_thread, NULL))
		return (1);
	if (!join_philos(philo, &data))
		return (1);
	if (simulation_finished(&data))
		close_simulation(&data);
	return (0);
}
