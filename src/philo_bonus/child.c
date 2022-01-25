/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:40:05 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 01:31:36 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosopher.h>
#include <act.h>
#include <timing.h>
#include <monitor.h>

t_bool	someone_died(t_philo philo)
{
	// pthread_mutex_lock(&philo.mutex->dead);
	if (sem_trywait(philo.died_sem) == 0)
	{
		sem_post(philo.died_sem);
		// sem_post(philo.died_sem);
		// sem_post(philo.died_sem);
		// pthread_mutex_unlock(&philo.mutex->dead);
		return (TRUE);
	}
	// pthread_mutex_unlock(&philo.mutex->dead);
	return (FALSE);
}

t_err	philo_child(t_philo *philo)
{
//	philo->settings->start_time = set_time();
	philo->last_eaten = philo->settings->start_time;
	if (pthread_create(&philo->monitor_thread, NULL, \
		&child_monitor_thread, philo) != 0)
		return (printf("Create_monitor_thread(philoID=%d) FAIL..\n", philo->id));
	while (!someone_died(*philo))
	{
		pthread_mutex_lock(&philo->mutex->full);
		if (is_full(*philo))
		{
			pthread_mutex_unlock(&philo->mutex->full);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex->full);
		// if (someone_died(*philo))
		// 	break ;
		grab_forks(philo);
		if (someone_died(*philo))
			break ;
		eat_now(philo);
		pthread_mutex_lock(&philo->mutex->full);
		if (someone_died(*philo) || is_full(*philo))
		{
			pthread_mutex_unlock(&philo->mutex->full);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex->full);
		sleep_now(philo);
		if (someone_died(*philo))
			break ;
		talk_now(*philo, THINK);
	}
	if (pthread_join(philo->monitor_thread, NULL) != 0)
		return (THR_JOIN_FAIL);
	return (NO_ERROR);
}
