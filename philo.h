#include <errno.h> 
#include <stdio.h> 
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_time_each_must_eat;
}	t_data;

typedef struct s_philo
{
	int X;
	int died;
	// other parameters I still dont know 
}	t_philo;

void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *s);
