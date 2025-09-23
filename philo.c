#include "philo.h"

void	*routine(void *arg)
{
	//aqui tiene que pasar toda la movida de comer dormimir y todo eso?¿
	pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
	pthread_mutex_lock(mutex);
	ft_putstr_fd("EATING\n", 1);
	pthread_mutex_unlock(mutex);
	pthread_mutex_lock(mutex);
	ft_putstr_fd("SLEEPING\n", 1);
	pthread_mutex_unlock(mutex);
	return NULL;
}

/* int	init_philosophers(t_data *data)
{
	int i;
	printf("Number of philosophers: %i.\n", data->num_philosophers);
	pthread_mutex_t mutex;
	pthread_t	t[data->num_philosophers];
	
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while(i < data->num_philos)
	{
		if(pthread_create(&t[i], NULL, &routine, &mutex) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return 1;
		}
		i++;
		pthread_mutex_lock(&mutex);
		printf("Thread %i created\n", i);
		pthread_mutex_unlock(&mutex);
	}
	i = 0;
	while(i < data->num_philos)
	{
		if(pthread_join(t[i], NULL) != 0)
		{
			ft_putstr_fd("Error finishing thread\n", 2);
			return 1;
		}
		i++;
		pthread_mutex_lock(&mutex);
		printf("Thread %i has finish\n", i);
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_destroy(&mutex);
	
	printf("Done\n");
	return (0);
} */

int	init_forks(pthread_mutex_t *forks, t_data *data)
{
	int i = 0;
	//tengo que reservar memoria si estoy declarandolo en el main?
	//data->forks = malloc(forks_num * sizeof(pthread_mutex_t));
	while(i < data->num_philos)
	{
		if(!pthread_mutex_init(&forks[i + 1], NULL))
		{
			perror("Error");
			return 0;	
		}
		i++;
	}
	return 1;
}

int init_philosophers(t_philo *philo, t_data *data, pthread_mutex_t *forks, pthread_t *threads)
{
	int i = 1;
	while(i <= data->num_philos)
	{
		philo->id = 1;
		philo->data = data;
		//cada filosofo coge en segundo lugar su tnedor con la izquierda (i)
		philo->r_fork = &forks[i];
		//cada filosofo coge primero el tenedor de su derecha (i + 1 )
		philo->l_fork = &forks[(i + 1) % data->num_philos];
		//inicializar todos los campos, por ahora no tengo mas
	}
	while(i <= data->num_philos)
	{
		//pthread_create(thread, attr, routine, arg)
		if(!pthread_create(&threads[i], NULL, philo_routine, (void *)&philo[i]))
			return 0;
	}
	return 1;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if((argc != 5) && (argc != 6))
	{
		ft_putstr_fd("Error\n", 2);
		return 1;
	}
	init_arguments(argv, &data, argc);
	if (!check_valid_argument(&data, argc))
	{
		ft_putstr_fd("Error\n", 2);
		return 1;
	}
	//Pero en C no puedes hacer eso exactamente de esa forma si data.num_philos no es una constante en tiempo de compilación.
/* 	pthread_mutex_t forks[data.num_philos];
	pthread_t philo[data.num_philos]; */
	pthread_mutex_t forks[MAX];
	t_philo philo[MAX];
	pthread_t threads[MAX];
	init_data(&data);
	if(!init_forks(forks, &data))
		return 1;
	//init data (?)
	if(!init_philosophers(philo, &data, threads))
		return 1;
	//start_meals()
	//end_meal()
	return 0;
}

