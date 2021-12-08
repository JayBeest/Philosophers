/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:05:11 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 22:30:09 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <philosopher.h>
#include <utils.h>

static t_err	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].settings = &info->settings;
		info->philos[i].forks_sem = info->forks_sem;
		info->philos[i].talk_sem = info->talk_sem;
		i++;
	}
	return (NO_ERROR);
}

t_err	init_struct(t_info *info)
{
	int	num_ph;

	num_ph = info->settings.num_philos;
	info->philos = (t_philo *)malloc(num_ph * sizeof(t_philo));
	if (!info->philos)
		return (MALLOC_FAIL);
	ft_bzero(info->philos, num_ph * sizeof(t_philo));
	// sem_unlink("talk");
	// sem_unlink("forkpile");
	info->forks_sem = sem_open("forkpile", O_CREAT | O_EXCL, 0644, num_ph);
	info->talk_sem = sem_open("talk", O_CREAT | O_EXCL, 0644, 1);
	if (errno != 0)
	{
		printf("THIS IS THE SEM_OPEN errno: %d msg: %s\n", errno, strerror(errno));
		return (MALLOC_FAIL);
	}
	init_philos(info);
	return (NO_ERROR);
}
