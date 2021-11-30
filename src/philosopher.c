/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:44 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 04:28:22 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

// void	sleep_now(t_msecs ms)
// {
// 	t_time_stamp	start;
// 	t_usecs			total_sleep;
// 	t_usecs			last_sleep;
// 	t_usecs			delta;


// 	ms *= 1000;
// 	start = set_start_time();


// }

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	static int	id;
	size_t 		us_since_start;

	philo = arg;
	us_since_start = passed(philo->settings->start_time, US);
	pthread_mutex_lock(&philo->mutex->id);
	id++;
//	printf("This is from thread %d ====>", id);
//	printf("Started after %zu us\n", us_since_start);
	printf("This is from PhiloID(%d) ====>Started after %zu us\n", philo->id, us_since_start);
	pthread_mutex_unlock(&philo->mutex->id);
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
		if (pthread_create(&info->philo[i].thread, NULL, &philo_thread, &info->philo[i]) != 0)
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

 t_err	init_philos(t_info *info)
 {
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		info->philo[i].id = i + 1;
		info->philo[i].settings = &info->settings;
		info->philo[i].mutex = &info->mutex;
		i++;
	}
	return (NO_ERROR);
 }

t_err	init_struct(t_info *info)
{
	int	num_ph;

	num_ph = info->settings.num_philos;
	info->philo = (t_philo *)malloc(num_ph * sizeof(t_philo));
	if (!info->philo)
		return (MALLOC_FAIL);
	ft_bzero(info->philo, num_ph * sizeof(t_philo));
	info->mutex.fork = (pthread_mutex_t *)malloc(num_ph * sizeof(pthread_mutex_t));
	if (!info->mutex.fork)
		return (MALLOC_FAIL);
	ft_bzero(info->mutex.fork, num_ph * sizeof(pthread_mutex_t));
	init_mutexes(info->settings.num_philos, &info->mutex);
	init_philos(info);
	info->settings.start_time = set_start_time();
	return (NO_ERROR);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (1);
	ft_bzero(&info, sizeof(info));
	if (parse_input(argc, argv, &info.settings) == FALSE)
		return (2);
	init_struct(&info);
	printf("ph_num=%d, die=%ld, eat=%ld, sleep=%ld, max_eat=%d\n", info.settings.num_philos, info.settings.die_time, info.settings.eat_time, info.settings.sleep_time, info.settings.max_eat);
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