/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:36 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 00:11:09 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>

t_bool	is_full(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->full);
	if (philo.times_eaten != philo.settings->max_eat)
	{
		pthread_mutex_unlock(&philo.mutex->full);
		return (FALSE);
	}
	philo.settings->done_eating++;
	pthread_mutex_unlock(&philo.mutex->full);
	return (TRUE);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->settings->max_eat == 0 || !is_full(*philo))
	{
		pthread_mutex_lock(&philo->mutex->dead);
		if (philo->settings->died)
		{
			pthread_mutex_unlock(&philo->mutex->dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex->dead);
		grab_forks(philo);
		eat_now(philo);
		pthread_mutex_lock(&philo->mutex->full);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->mutex->full);
		sleep_now(philo);
		think_now(philo);
	}
	return (NULL);
}

int	check_death_timer(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		if ((info.settings.max_eat == 0 || !is_full(info.philo[i])) && \
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
		{
			pthread_mutex_unlock(&info->mutex.full);
			return (NULL);
		}
		pthread_mutex_unlock(&info->mutex.full);
		pthread_mutex_lock(&info->mutex.dead);
		info->settings.died = check_death_timer(*info);
		pthread_mutex_unlock(&info->mutex.dead);
	}
	talk_now(*info->philo, DIE);
	return (NULL);
}
