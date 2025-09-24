#include "philo.h"

long	get_time_ms(void)
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
	time = get_time_ms() - start_time;
	return (time);
}

/* int main()
{
	long long program_start = get_time_ms();
	printf("Something happend at %lld\n", get_timestamp(program_start));
	usleep(40000);
	printf("Something happend at %lld\n", get_timestamp(program_start));
	return 0;
} */