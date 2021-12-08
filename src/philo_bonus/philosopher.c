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
#include <unistd.h>
#include <philosopher.h>
#include <parser.h>
#include <init.h>
#include <timing.h>
#include <threads.h>
#include <utils.h>

#include <sys/errno.h>
#include <stdio.h>

int	free_stuff(t_info info, int return_value)
{
	free(info.philos);
	// free(info.mutex.forks);
	return (return_value);
}

int	destroy(t_info *info)
{
	printf("sem_unlink(forkpile) rv =%d err=%s\n", sem_unlink("forkpile"), strerror(errno));
	printf("sem_close(forkpile) rv=%d err=%s\n", sem_close(info->forks_sem), strerror(errno));
	printf("sem_unlink(talk) rv =%d err=%s\n", sem_unlink("talk"), strerror(errno));
	printf("sem_close(talk) rv=%d err=%s\n", sem_close(info->talk_sem), strerror(errno));
	return (0);
}

int	start_philos(t_info *info)
{
	int	id;
	int	i;

	i = 0;
	info->settings.start_time = set_time();
	while (i < info->settings.num_philos)
	{
		info->philos[i].last_eaten = info->settings.start_time;
		id = fork();
		if (id == -1)
			return (printf("Fork FAIL (philo[%d])\n", i));
		else if (id == 0)
			break ;
		info->philos[i].pid = id;
		i++;
	}
	if (id == 0)
	{
		philo_thread(&info->philos[i]); /// <=======HIERO BEN JE
		exit (0);
	}
	else if (pthread_create(&info->monitor, NULL, &monitor_thread, info) != 0)
		return (printf("Thread_create FAIL (monitor)\n"));
	return (0);
}
  
int	wait_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		wait(NULL);
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
	if (init_struct(&info) == MALLOC_FAIL)
		return (3);
	if (start_philos(&info) != 0)
		return (free_stuff(info, 4));
	if (wait_philos(&info) != 0)
		return (free_stuff(info, 5));
	if (destroy(&info) != 0)
		return (free_stuff(info, 6));
	return (free_stuff(info, 0));
}
