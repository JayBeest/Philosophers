#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <philosopher.h>

void	ft_bzero(void *ptr, size_t n)
{
	while (n > 0)
	{
		*(char *)ptr = 0;
		ptr++;
		n--;
	}
}

t_timing	set_start_time(void)
{
	t_timing		new;
	struct timeval	current;

	gettimeofday(&current, NULL);
	new.sec = current.tv_sec;
	new.usec = current.tv_usec;
	printf("start time:%ld milis: %d\n", current.tv_sec, current.tv_usec);
	return (new);
}

size_t	time_passed(t_timing start)
{
	size_t			passed;
	struct timeval	current;

	gettimeofday(&current, NULL);
	passed = (current.tv_sec - start.sec) * 1000000 + current.tv_usec - start.usec;
	return (passed);
}

int	main(int argc, char **argv)
{
	t_info	info;
	(void)argc;
	(void)argv;

	ft_bzero(&info, sizeof(info));
	int i = 20;
	info.start_time = set_start_time();

	while (i > 0)
	{
		usleep(500);
	printf("Passed time: %zu\n", time_passed(info.start_time));
	i--;	
	}
	return 0;
}