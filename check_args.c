#include "philo.h"

void	init_arguments(char *argv[], t_data *data, int argc)
{
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_of_time_each_must_eat = ft_atoi(argv[5]);
	else 
		data->num_of_time_each_must_eat = 0;
}

int	 check_valid_argument(t_data *data, int argc)
{
	if (data->num_philosophers < 1 || data->num_philosophers > 200)
		return 0;
	else if ((data->time_to_die <= 0) || (data->time_to_eat <= 0) || (data->time_to_sleep <= 0))
		return 0;
	else if (argc == 6 && data->num_of_time_each_must_eat <= 0)
		return 0;
	return 1;
}