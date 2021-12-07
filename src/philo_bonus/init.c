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
#include <semaphores.h>
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
		info->philos[i].forks = &info->forks;
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
	sem_init(&info->forks, 0, num_ph);
	init_philos(info);
	return (NO_ERROR);
}
