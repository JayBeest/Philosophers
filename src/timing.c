#include <unistd.h>
#include <philosopher.h>
#include <sys/time.h>

t_time_stamp	set_start_time(void)
{
	t_time_stamp	time_stamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_stamp.sec = current.tv_sec;
	time_stamp.usec = current.tv_usec;
	return (time_stamp);
}

long	passed(t_time_stamp start, t_time_unit time_unit)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (time_unit == US)
		return ((current.tv_sec - start.sec) * 1000000 + (current.tv_usec - start.usec) );
	else if (time_unit == MS)
		return ((current.tv_sec - start.sec) * 1000 + (current.tv_usec - start.usec) / 1000);
	return ((current.tv_sec - start.sec) + (current.tv_usec - start.usec) / 1000000);
}

void	sleep_now(t_msecs ms)
{
	t_time_stamp	start;

	start = set_start_time();
	while (ms - passed(start, MS) > 0)
		usleep(100);
}
