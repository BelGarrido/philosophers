#include "philo.h"

void	*routine()
{
	ft_putstr_fd("Thread routine done\n", 1);
}

int	create_philosophers(t_data *data)
{
	int i;
	printf("Number of philosophers: %i.\n", data->num_philosophers);

	pthread_t	t[data->num_philosophers];
	pthread_mutex_t mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while(i < data->num_philosophers)
	{
		//pthread_mutex_lock(&mutex);
		if(pthread_create(&t[i], NULL, &routine, NULL) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return 1;
		}
		i++;
		printf("Thread %i created\n", i);
		//pthread_mutex_unlock(&mutex);
	}
	i = 0;
	while(i < data->num_philosophers)
	{
		if(pthread_join(t[i], NULL) != 0)
		{
			ft_putstr_fd("Error finishing thread\n", 2);
			return 1;
		}
		printf("Thread %i has finish\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Done\n");
	return (0);
}

void	init_data(char *argv[], t_data *data, int argc)
{
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_of_time_each_must_eat = ft_atoi(argv[5]);
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if((argc != 5) && (argc != 6))
	{
		ft_putstr_fd("Error\n", 2);
		return 1;
	}
	init_data(argv, &data, argc);
	if(create_philosophers(&data) != 0)
	{
		return 1;
	}
	return 0;
}

