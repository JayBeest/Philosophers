/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:44 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/13 20:20:07 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <philosopher.h>
#include <parser.h>
#include <init.h>
#include <timing.h>
#include <monitor.h>
#include <child.h>
#include <talk2.h>
#include <utils.h>

int	free_stuff(t_info info, int return_value)
{
	free(info.philos);
	return (return_value);
}

int	destroy(t_info *info)
{
	sem_unlink("forkpile");
	sem_close(info->forks_sem);
	sem_unlink("talk");
	sem_close(info->talk_sem);
	sem_unlink("died");
	sem_close(info->died_sem);
	return (0);
}

int	spawn_philos(t_info *info)
{
	int	id;
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		id = fork();
		if (id == -1)
			return (printf("Fork FAIL (philo[%d])\n", i));
		else if (id == 0)
		{
			philo_child(&info->philos[i]);
			exit (0);
		}
		kill(id, SIGSTOP);
		info->philos[i].pid = id;
		i++;
	}
	start_sim(info);
	info->settings.start_time = set_time();
	return (0);
}

int	wait_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		waitpid(0, NULL, 0);
		i++;
	}
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
	if (spawn_philos(&info) != 0)
		return (free_stuff(info, 4));
	if (wait_philos(&info) != 0)
		return (free_stuff(info, 5));
	if (destroy(&info) != 0)
		return (free_stuff(info, 6));
	return (free_stuff(info, 0));
}
