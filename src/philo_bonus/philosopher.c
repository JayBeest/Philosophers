/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:44 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 05:15:34 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <philosopher.h>
#include <parser.h>
#include <init.h>
#include <timing.h>
#include <child.h>
#include <talk2.h>
#include <utils.h>

static void	destroy(void)
{
	sem_unlink("forkpile");
	sem_unlink("talk");
	sem_unlink("died");
	sem_unlink("death");
}

static int	free_stuff(t_info info, int return_value)
{
	free(info.philos);
	destroy();
	return (return_value);
}

static int	spawn_philos(t_info *info)
{
	int	id;
	int	i;

	i = 0;
	info->settings.start_time = set_time();
	while (i < info->settings.num_philos)
	{
		id = fork();
		if (id == -1)
			return (printf("Fork FAIL (philo[%d])\n", i));
		else if (id == 0)
		{
			if (philo_child(&info->philos[i]) == THR_JOIN_FAIL)
				exit (printf("Thread join FAIL (philo[%d])\n", i));
			exit (0);
		}
		info->philos[i].pid = id;
		i++;
	}
	init_signal();
	return (0);
}

static void	wait_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (say_usage_error(1));
	ft_bzero(&info, sizeof(info));
	if (parse_input(argc, argv, &info.settings) == FALSE)
		return (say_usage_error(2));
	if (init_struct(&info) == MALLOC_FAIL)
		return (printf("Malloc fail\n"));
	if (init_mutexes(&info.mutex) == MUTEX_FAIL)
		return (printf("Mutex fail\n"));
	if (info.settings.num_philos == 1)
	{
		single_philo(*info.philos);
		return (free_stuff(info, 0));
	}
	if (spawn_philos(&info) != 0)
		return (free_stuff(info, 3));
	wait_philos(&info);
	return (free_stuff(info, 0));
}
