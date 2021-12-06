/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:36 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/06 20:55:36 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->settings->max_eat == 0 || \
		philo->times_eaten < philo->settings->max_eat)
	{
		grab_forks(philo);
		eat_now(philo);
		philo->times_eaten++;
		sleep_now(philo);
		think_now(philo);
	}
	if (philo->times_eaten == philo->settings->max_eat)
	{
		pthread_mutex_lock(&philo->mutex->full);
		philo->settings->done_eating++;
		pthread_mutex_unlock(&philo->mutex->full);
	}
	return (NULL);
}

int	check_death_timer(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		if ((info.settings.max_eat == 0 || \
			info.philo[i].times_eaten < info.settings.max_eat) && \
			passed(info.philo[i].last_eaten, MS) > info.settings.die_time)
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (info->settings.died == 0)
	{
		usleep(INTERVAL);
		pthread_mutex_lock(&info->mutex.full);
		if (info->settings.done_eating == info->settings.num_philos)
			return (NULL);
		pthread_mutex_unlock(&info->mutex.full);
		pthread_mutex_lock(&info->mutex.dead);
		info->settings.died = check_death_timer(*info);
		pthread_mutex_unlock(&info->mutex.dead);
	}
	talk_now(*info->philo, DIE);
	return (NULL);
}
