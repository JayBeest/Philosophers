/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:36 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 02:14:51 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>

t_bool	noone_died(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->dead);
	if (philo.settings->died)
	{
		pthread_mutex_unlock(&philo.mutex->dead);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo.mutex->dead);
	return (TRUE);
}

t_bool	is_full(t_philo philo, t_bool only_checking)
{
	pthread_mutex_lock(&philo.mutex->full);
	if (philo.times_eaten != philo.settings->max_eat)
	{
		pthread_mutex_unlock(&philo.mutex->full);
		return (FALSE);
	}
	if (!only_checking)
		philo.settings->done_eating++;
	pthread_mutex_unlock(&philo.mutex->full);
	return (TRUE);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while ((philo->settings->max_eat == 0 || !is_full(*philo, FALSE)) && \
		noone_died(*philo))
	{
		grab_forks(philo);
		if (noone_died(*philo))
			eat_now(philo);
		if (noone_died(*philo))
			sleep_now(philo);
		if (noone_died(*philo))
			talk_now(*philo, THINK);
	}
	drop_forks(*philo);
	return (NULL);
}

int	check_death_timer(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		if (!is_full(info.philos[i], TRUE) && \
			passed(info.philos[i].last_eaten, MS) > info.settings.die_time)
			return (i + 1);
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
	talk_now(*info->philos, DIE);
	return (NULL);
}
