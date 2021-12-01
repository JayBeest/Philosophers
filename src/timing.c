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
	if (time_unit == S)
		return ((current.tv_sec - start.sec) * 1 + (current.tv_usec - start.usec) / 1000000);
	else if (time_unit == MS)
		return ((current.tv_sec - start.sec) * 1000 + (current.tv_usec - start.usec) / 1000);
	return ((current.tv_sec - start.sec) * 1000000 + (current.tv_usec - start.usec));
}

void	sleep_now(t_msecs ms)
{
	t_time_stamp	start;
	t_usecs			total_sleep;
	t_usecs			next_sleep;
	int				i;

	i = 1;
	next_sleep = 1000;
	ms *= 1;
	start = set_start_time();
	while (i <= ms)
	{	
		usleep(next_sleep);
		next_sleep += 1000 * i - passed(start, US) + 256;
		if (next_sleep < 0)
			next_sleep = 0;
		// total_sleep = passed(start, US);
		// printf("total_sleep =%lu us ==>next_sleep=%lu us\n", total_sleep, next_sleep);
		i++;
	}
	total_sleep = passed(start, US);
	printf("\ncustom_sleep offset = %ld\n", total_sleep - ms * 1000);

	// printf("\n====>CHANGE<====\n\n");
	int delta = 101;
	int count = 0;
	while (delta > 50)
	{
	start = set_start_time();
	usleep(ms*1000);
	total_sleep = passed(start, US);
	delta = total_sleep - ms * 1000;
	count++;
	}
	printf("\nplain_old_usleep offset = %ld us only after %d iterations\n\n", total_sleep - ms * 1000, count);
}