/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:48 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 02:30:07 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <philosopher.h>
#include <utils.h>

static void	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].settings = &info->settings;
		info->philos[i].mutex = &info->mutex;
		if (i == 0)
		{
			info->philos[i].right_fork = \
				&info->mutex.forks[info->settings.num_philos - 1];
			info->philos[i].left_fork = &info->mutex.forks[i];
		}
		else
		{
			info->philos[i].right_fork = &info->mutex.forks[i - 1];
			info->philos[i].left_fork = &info->mutex.forks[i];
		}
		i++;
	}
}

t_err	init_mutexes(int num_philos, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&mutex->forks[i], NULL) != 0)
			return (MUTEX_FAIL);
		i++;
	}
	if (pthread_mutex_init(&mutex->dead, NULL) != 0)
		return (MUTEX_FAIL);
	if (pthread_mutex_init(&mutex->full, NULL) != 0)
		return (MUTEX_FAIL);
	if (pthread_mutex_init(&mutex->talk, NULL) != 0)
		return (MUTEX_FAIL);
	return (NO_ERROR);
}

t_err	init_structs(t_info *info)
{
	int	num_ph;

	num_ph = info->settings.num_philos;
	info->philos = (t_philo *)malloc(num_ph * sizeof(t_philo));
	if (!info->philos)
		return (MALLOC_FAIL);
	ft_bzero(info->philos, num_ph * sizeof(t_philo));
	info->mutex.forks = (pthread_mutex_t *)malloc(num_ph * \
		sizeof(pthread_mutex_t));
	if (!info->mutex.forks)
	{
		free(info->philos);
		return (MALLOC_FAIL);
	}
	ft_bzero(info->mutex.forks, num_ph * sizeof(pthread_mutex_t));
	init_philos(info);
	return (NO_ERROR);
}
