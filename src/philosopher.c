/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:44 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 02:04:44 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	passed(t_time_stamp start, t_time_unit time_unit)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (time_unit == S)
		return ((current.tv_sec - start.sec) * 1 + (current.tv_usec - start.usec) / 1000000);
	else if (time_unit == MS)
		return ((current.tv_sec - start.sec) * 1000 + (current.tv_usec - start.usec) / 1000);
	return ((current.tv_sec - start.sec) * 1000000 + (current.tv_usec - start.usec));
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

void	*philo_thread(void *arg)
{
	t_info		*info;
	static int	id;

	id++;
	info = (t_info *)arg;
	printf("This is from thread %d ====>", id);
	printf("Started after %zu us\n", passed(info->start_time, US));
//	printf("Started after %zu ms\n", passed(info->start_time, MS));
//	printf("Started after %zu s\n", passed(info->start_time, S));
	return NULL;
}

void	start_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		if (pthread_create(&info->philo[i].thread, NULL, &philo_thread, info) != 0)
			printf("Thread_create FAIL (philo[%d]) -->errno=%d\n", i, errno);
		i++;
	}
}

void	join_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			printf("Thread_join FAIL (philo[%d]) -->errno=%d\n", i, errno);
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

//	int i = 20;
//	while (i > 0)
//	{
//		usleep(500000);
//		size_t nu = ms_passed(info.start_time);
//		printf("Passed time: %lu ms\n", nu);
//		i--;
//	}
	join_philos(&info);
	destroy_mutexes(info.settings.num_philos, &info.mutex);
	return 0;
}