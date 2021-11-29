#include <unistd.h>
#include <sys/time.h>
#include <philosopher.h>
#include <parser.h>
#include <utils.h>

#include <sys/errno.h>

t_time_stamp	set_start_time(void)
{
	t_time_stamp	time_stamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_stamp.sec = current.tv_sec;
	time_stamp.usec = current.tv_usec;
	return (time_stamp);
}

size_t	ms_passed(t_time_stamp start)
{
	size_t			passed;
	struct timeval	current;

	gettimeofday(&current, NULL);
	passed = (current.tv_sec - start.sec) * 1000 + (current.tv_usec - start.usec) / 1000;
	return (passed);
}

void	*philo_thread()
{
	// (void)info;
	static int i = 0;
	i++;
	printf("This is from the thread int=%d\n", i);
	return NULL;
}

t_bool	init_mutexes(int num_philos, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&mutex->fork[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_mutex_init(&mutex->dead, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

void	destroy_mutexes(int num_philos, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(&mutex->fork[i]) != 0)
			printf("mutex_destroy FAIL (fork[%d]) -->errno=%d\n", i, errno);
		i++;
	}
	if (pthread_mutex_destroy(&mutex->dead) != 0)
		printf("mutex_destroy FAIL (dead) -->errno=%d\n", errno);
}

void	start_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		if (pthread_create(&info->philo[i].thread, NULL, philo_thread, NULL) != 0)
			printf("Thread_create FAIL (philo[%d]) -->errno=%d\n", i, errno);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (1);
	ft_bzero(&info, sizeof(info));
	if (parse_input(argc, argv, &info.settings) == FALSE)
		return (2);
	printf("ph_num=%d, die=%d, eat=%d, sleep=%d, max_eat=%d\n", info.settings.num_philos, info.settings.die_time, info.settings.eat_time, info.settings.sleep_time, info.settings.max_eat);
	init_mutexes(info.settings.num_philos, &info.mutex);
	info.start_time = set_start_time();
	start_philos(&info);

	int i = 20;
	while (i > 0)
	{
		usleep(500000);
		size_t nu = ms_passed(info.start_time);
		printf("Passed time: %lu ms\n", nu);
		i--;	
	}

	destroy_mutexes(info.settings.num_philos, &info.mutex);
	return 0;
}