/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:25:06 by jcorneli          #+#    #+#             */
/*   Updated: 2022/01/27 01:44:41 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>
#include <child.h>

static t_bool	check_death_timer(t_philo philo)
{
	int	i;

	if (ms_passed(philo.last_eaten) > philo.settings->die_time)
	{
		i = 0;
		while (i < philo.settings->num_philos)
		{
			sem_post(philo.died_sem);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

static void	drop_forks(t_philo philo)
{
	int	i;

	i = 0;
	while (i < philo.settings->num_philos)
	{
		sem_post(philo.forks_sem);
		i++;
	}
}

t_bool	is_full(t_philo philo)
{
	if (philo.settings->max_eat == 0 || \
			philo.times_eaten != philo.settings->max_eat)
		return (FALSE);
	return (TRUE);
}

void	*child_monitor_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!someone_died(*philo))
	{
		usleep(MONITORING_INTERVAL);
		pthread_mutex_lock(&philo->mutex->full);
		if (is_full(*philo) || someone_died(*philo))
		{
			pthread_mutex_unlock(&philo->mutex->full);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex->full);
		pthread_mutex_lock(&philo->mutex->dead);
		philo->settings->died = check_death_timer(*philo);
		pthread_mutex_unlock(&philo->mutex->dead);
	}
	if (sem_trywait(philo->first_dying_sem) == 0)
	{
		talk_now(*philo, DIE);
		drop_forks(*philo);
	}
	return (NULL);
}
