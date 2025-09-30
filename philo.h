/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:55:09 by anagarri          #+#    #+#             */
/*   Updated: 2025/09/30 17:55:14 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h> 
#include <stdio.h> 
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef MAX
#define MAX 200
#endif

struct s_philo;
struct s_data;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_time_must_eat;
	long			start_time;			// Tiempo de inicio del programa
	int				philo_dead;	
	int				simulation_is_completed;		// Flag para terminar simulación
	pthread_mutex_t	*forks;				// Array de mutex para tenedores
	pthread_mutex_t	print_mutex;		// Mutex para imprimir sin mezclar
	pthread_mutex_t	death_mutex;		// Mutex para verificar muerte
	pthread_mutex_t	monitor_mutex;
	pthread_t		monitor_thread;
	struct s_philo	*philosophers;
}	t_data;

typedef struct s_philo
{
	int				id;						// ID del filósofo (1 a N)
	int				meals_count;
	int				is_eating;			// Veces que ha comido
	long 			last_meal_time;			// Timestamp de última comida
	//pthread_mutex_t mutex_philo;
	pthread_t 		thread;
	t_data 			*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	eating_mutex;
	// other parameters I still dont know 
}	t_philo;

/*Actions*/
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);
/*Check_args*/
void	init_arguments(char **argv, t_data *data, int argc);
int		check_valid_argument(char **argv, int argc);
int		ft_atoi(const char *s);
/* Routine.c*/
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
/*Get_time.c*/
long	get_timestamp(long start_time);
long	get_time_ms(void);
void	ft_usleep(long int miliseconds);
/*Utils*/
void	ft_putstr_fd(char *s, int fd);
void	print_locked(t_philo *philo, char *msg);
