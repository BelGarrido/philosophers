#include <errno.h> 
#include <stdio.h> 
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef MAX
#define MAX 200
#endif

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_time_each_must_eat;
	long	start_time;			// Tiempo de inicio del programa
	int		simulation_end;		// Flag para terminar simulación
	pthread_mutex_t	*forks;				// Array de mutex para tenedores
	pthread_mutex_t	print_mutex;		// Mutex para imprimir sin mezclar
	pthread_mutex_t	death_mutex;		// Mutex para verificar muerte
	t_philo	*philosophers;

}	t_data;

typedef struct s_philo
{
	int	id;						// ID del filósofo (1 a N)
	int	meals_count;			// Veces que ha comido
	long last_meal_time;		// Timestamp de última comida
	//pthread_mutex_t mutex_philo;
	t_data *data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	// other parameters I still dont know 
}	t_philo;


/*Check_args*/
void	init_arguments(char *argv[], t_data *data, int argc);
int	check_valid_argument(t_data *data, int argc);
/*Get_time.c*/
long	get_timestamp(long start_time);
long	time_to_miliseconds(void);

void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *s);
