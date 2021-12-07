/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:44 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 02:06:26 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <philosopher.h>
#include <parser.h>
#include <init.h>
#include <timing.h>
#include <threads.h>
#include <utils.h>

#include <sys/errno.h>
#include <stdio.h>

void	destroy_mutexes(int num_philos, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(&mutex->forks[i]) != 0)
			printf("mutex_destroy FAIL (fork[%d]) -->errno=%d\n", i, errno);
		i++;
	}
	if (pthread_mutex_destroy(&mutex->dead) != 0)
		printf("mutex_destroy FAIL (dead) -->errno=%d\n", errno);
	if (pthread_mutex_destroy(&mutex->talk) != 0)
		printf("mutex_destroy FAIL (talk) -->errno=%d\n", errno);
	if (pthread_mutex_destroy(&mutex->full) != 0)
		printf("mutex_destroy FAIL (full) -->errno=%d\n", errno);
}

void	start_philos(t_info *info)
{
	int	i;

	i = 0;
	info->settings.start_time = set_start_time();
	while (i < info->settings.num_philos)
	{
		info->philos[i].last_eaten = info->settings.start_time;
		if (pthread_create(&info->philos[i].thread, NULL, &philo_thread, \
			&info->philos[i]) != 0)
			printf("Thread_create FAIL (philos[%d]) -->errno=%d\n", i, errno);
		i++;
	}
	if (pthread_create(&info->monitor, NULL, &monitor_thread, info) != 0)
		printf("Monitor_thread_create FAIL!! -->errno=%d\n", errno);
}

void	join_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			printf("Thread_join FAIL (philos[%d]) -->errno=%d\n", i, errno);
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
		printf("Thread_join FAIL (monitor) -->errno=%d\n", errno);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (1);
	ft_bzero(&info, sizeof(info));
	if (parse_input(argc, argv, &info.settings) == FALSE)
		return (2);
	if (init_struct(&info) == MALLOC_FAIL)
		return (3);
	start_philos(&info);
	join_philos(&info);
	destroy_mutexes(info.settings.num_philos, &info.mutex);
	free(info.philos);
	free(info.mutex.forks);
	return (0);
}
