/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:31:49 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/14 18:04:06 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define MAX 200

struct	s_philo;
struct	s_data;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_time_must_eat;
	long			start_time;			// Tiempo de inicio del programa
	int				philo_dead;	
	int				simulation_is_completed; // Flag para terminar simulación
	pthread_mutex_t	*forks;				// Array de mutex para tenedores
	pthread_mutex_t	print_mutex;		// Mutex para imprimir sin mezclar
	pthread_mutex_t	death_mutex;		// Mutex para verificar muerte
	pthread_mutex_t	monitor_mutex;
	pthread_t		monitor_thread;
	struct s_philo	*philosophers;
}	t_data;

typedef struct s_philo
{
	int				id;					// ID del filósofo (1 a N)
	int				meals_count;
	long			last_meal_time;		// Timestamp de última comida
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	meals_mutex;
}	t_philo;

/* check_args.c */
int		check_valid_argument(char **argv, int argc); // check_args.c
int		ft_atoi(const char *s); // check_args.c

/* actions.c */
void	eat(t_philo *philo); // actions.c
int		take_forks(t_philo *philo); // actions.c
int		close_simulation(t_data *data); // actions.c

/* routine.c */
void	*monitor_routine(void *arg); // routine.c
void	*philo_routine(void *arg); // routine.c

/* finalization_checks.c */
int		simulation_finished(t_data *data); // finalization_checks.c
int		any_philo_dead(t_data *data); // finalization_checks.c
int		check_if_all_ate(t_data *data);

/* utils.c */
long	get_timestamp(long start_time); // utils.c
long	get_time_ms(void); // utils.c
void	ft_usleep(long time, t_data *data); // utils.c
void	print_locked(t_philo *philo, char *msg); // utils.c

#endif