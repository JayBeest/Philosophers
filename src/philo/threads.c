/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:36 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 02:55:34 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>

#include <stdio.h>

t_bool	someone_died(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->dead);
	if (philo.settings->died)
	{
		pthread_mutex_unlock(&philo.mutex->dead);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo.mutex->dead);
	return (FALSE);
}

t_bool	is_full(t_philo philo)
{
	if (philo.settings->max_eat == 0)
		return (FALSE);
	pthread_mutex_lock(&philo.mutex->full);
	if (philo.times_eaten != philo.settings->max_eat)
	{
		pthread_mutex_unlock(&philo.mutex->full);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo.mutex->full);
	return (TRUE);
}

int	check_death_timer(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		if (!is_full(info.philos[i]) && \
			ms_passed(info.philos[i].last_eaten) > info.settings.die_time)
			return (i + 1);
		i++;
	}
	return (0);
}

t_bool	should_stop_cycle(t_philo philo)
{
	t_bool	done_eating;
	t_bool	one_died;

	done_eating = FALSE;
	one_died = someone_died(philo);
	if (!one_died && philo.settings->max_eat != 0)
		done_eating = is_full(philo);
	return (one_died || done_eating);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!should_stop_cycle(*philo))
	{
		grab_forks(philo);
		if (someone_died(*philo))
			break ;
		eat_now(philo);
		if (should_stop_cycle(*philo))
			break ;
		sleep_now(philo);
		if (someone_died(*philo))
			break ;
		talk_now(*philo, THINK);
	}
	drop_forks(*philo);
	return (NULL);
}

void	*monitor_thread(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (info->settings.died == 0)
	{
		usleep(MONITORING_INTERVAL);
		pthread_mutex_lock(&info->mutex.full);
		if (info->settings.nr_philos_full == info->settings.num_philos)
		{
			pthread_mutex_unlock(&info->mutex.full);
//			pthread_mutex_lock(&info->mutex.dead);
//			info->settings.died = -1;
//			pthread_mutex_unlock(&info->mutex.dead);
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
