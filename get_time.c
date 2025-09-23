#include "philo.h"

long	time_to_miliseconds(void)
{
	struct timeval tv;
	long int time;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
long	get_timestamp(long start_time)
{
	long long time;
	time = time_to_miliseconds() - start_time;
	return (time);
}

/* int main()
{
	long long program_start = time_to_miliseconds();
	printf("Something happend at %lld\n", get_timestamp(program_start));
	usleep(40000);
	printf("Something happend at %lld\n", get_timestamp(program_start));
	return 0;
} */