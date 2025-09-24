#include "philo.h"

void	*philo_routine(void *arg)
{
	//aqui tiene que pasar toda la movida de comer dormimir y todo eso?¿
	t_philo *philo = (t_philo*)arg;
	printf("This is the function routine with philo[%i]\n", philo->id);
	if((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%i has taken its right fork\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		if(pthread_mutex_lock(philo->l_fork))
			pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%i has taken its left fork\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
	}
	if((philo->id % 2) != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%i has taken its left fork\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		if(pthread_mutex_lock(philo->r_fork))
			pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%i has taken its right fork\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
	}
/* 	pthread_mutex_lock(mutex);
	ft_putstr_fd("EATING\n", 1);
	pthread_mutex_unlock(mutex);
	pthread_mutex_lock(mutex);
	ft_putstr_fd("SLEEPING\n", 1);
	pthread_mutex_unlock(mutex);*/
	return NULL;
}

int	init_forks(pthread_mutex_t *forks, t_data *data)
{
	int i = 0;
	//tengo que reservar memoria si estoy declarandolo en el main?
	//data->forks = malloc(forks_num * sizeof(pthread_mutex_t));
	while(i < data->num_philos)
	{
		//si sale bien devuelve 0, si falla 1
		if(pthread_mutex_init(&forks[i], NULL))
		{
			perror("Error");
			return 0;	
		}
		i++;
		printf("creando_fork numero %i\n", i);
	}

	return 1;
}

int init_philosophers(t_philo *philo, t_data *data)
{
	int i = 0;
	while(i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_count = 0;
		philo[i].last_meal_time = 0;
		philo[i].data = data;
		//cada filosofo coge en segundo lugar su tnedor con la izquierda (i)
		philo[i].r_fork = &data->forks[i];
		//cada filosofo coge primero el tenedor de su derecha (i + 1)
		philo[i].l_fork = &data->forks[(i + 1) % data->num_philos];
		//inicializar todos los campos, por ahora no tengo mas
		philo[i].print_mutex = &data->print_mutex;
		philo[i].death_mutex = &data->death_mutex;
		printf("creando_philosopher numero %i\n", i + 1);
		i++;
	}
	i = 0;
	while(i < data->num_philos)
	{
		//pthread_create(thread, attr, routine, arg) vamos creando hilos en cada philosofo
		//si se crea el hilo correctamente devuelve 0, si no devuelve 1
		if(pthread_create(&philo[i].thread, NULL, philo_routine, (void *)&philo[i]) != 0)
			return 0;
		printf("creando_threads numero %i\n", philo[i].id);
		i++;
	}
	i = 0;
	while(i < data->num_philos)
	{
		if(pthread_join(philo[i].thread, NULL))
			return 0;
		printf("joining_threads numero %i\n", philo[i].id);
		i++;
	}
	return 1;
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

	data->philo_dead = 0;
	data->start_time = get_time_ms();

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);

	data->philosophers = NULL;
	data->forks = NULL;
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	philo[MAX];
	pthread_mutex_t forks[MAX];
	//pthread_t threads[MAX];
	if (!check_valid_argument(argv, argc))
		return 1;
	//Pero en C no puedes hacer eso exactamente de esa forma si data.num_philos no es una constante en tiempo de compilación.
/* 	pthread_mutex_t forks[data.num_philos];
	pthread_t philo[data.num_philos]; */
	init_data(&data, argv);
	data.philosophers = philo;
    data.forks = forks;
	if(!init_forks(forks, &data))
		return 1;
	if(!init_philosophers(philo, &data))
		return 1;
	return 0;
}

