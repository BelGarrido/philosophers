#include "philo.h"

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

void ft_usleep(long int miliseconds)
{
	long int		start;
	start = get_time_ms();
	while((get_time_ms() - start) < miliseconds)
		usleep(100);
}

/* int main()
{
	long long program_start = get_time_ms();
	printf("Something happend at %lld\n", get_timestamp(program_start));
	usleep(40000);
	printf("Something happend at %lld\n", get_timestamp(program_start));
	return 0;
} */