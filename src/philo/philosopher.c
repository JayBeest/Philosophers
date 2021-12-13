/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:44 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 02:30:07 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <philosopher.h>
#include <parser.h>
#include <init.h>
#include <timing.h>
#include <threads.h>
#include <talk2.h>
#include <utils.h>

#include <sys/errno.h>
#include <stdio.h>

int	free_stuff(t_info info, int return_value)
{
	free(info.philos);
	free(info.mutex.forks);
	return (return_value);
}

int	destroy_mutexes(int num_philos, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(&mutex->forks[i]) != 0)
			return (printf("mutex_destroy FAIL (fork[%d])\n", i));
		i++;
	}
	if (pthread_mutex_destroy(&mutex->dead) != 0)
		return (printf("mutex_destroy FAIL (dead)\n"));
	if (pthread_mutex_destroy(&mutex->talk) != 0)
		return (printf("mutex_destroy FAIL (talk)\n"));
	if (pthread_mutex_destroy(&mutex->full) != 0)
		return (printf("mutex_destroy FAIL (full)\n"));
	return (0);
}

int	start_philos(t_info *info)
{
	int	i;

	i = 0;
	info->settings.start_time = set_time();
	while (i < info->settings.num_philos)
	{
		info->philos[i].last_eaten = info->settings.start_time;
		if (pthread_create(&info->philos[i].thread, NULL, &philo_thread, \
			&info->philos[i]) != 0)
			return (printf("Thread_create FAIL (philo[%d])\n", i));
		i++;
	}
	if (pthread_create(&info->monitor, NULL, &monitor_thread, info) != 0)
		return (printf("Thread_create FAIL (monitor)\n"));
	return (0);
}

int	join_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (printf("Thread_join FAIL (philos[%d])\n", i));
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
		return (printf("Thread_join FAIL (monitor)\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (1);
	ft_bzero(&info, sizeof(info));
	if (parse_input(argc, argv, &info.settings) == FALSE)
		return (2);
	if (info.settings.num_philos == 1)
		return (return_single_philo());
	if (init_struct(&info) == MALLOC_FAIL)
		return (3);
	if (start_philos(&info) != 0)
		return (free_stuff(info, 4));
	if (join_philos(&info) != 0)
		return (free_stuff(info, 5));
	if (destroy_mutexes(info.settings.num_philos, &info.mutex) != 0)
		return (free_stuff(info, 6));
	return (free_stuff(info, 0));
}
