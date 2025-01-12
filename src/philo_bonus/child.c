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
#include <monitor.h>

t_bool	someone_died(t_philo philo)
{
	if (sem_trywait(philo.died_sem) == 0)
	{
		sem_post(philo.died_sem);
		return (TRUE);
	}
	return (FALSE);
}

t_err	philo_child(t_philo *philo)
{
	philo->last_eaten = philo->settings->start_time;
	if (pthread_create(&philo->monitor_thread, NULL, \
		&child_monitor_thread, philo) != 0)
		return (printf("Create_monitor_thread(philoID=%d) FAIL..\n", philo->id));
	while (!is_full(*philo) && !someone_died(*philo))
	{
		if (someone_died(*philo))
			break ;
		grab_forks(philo);
		if (someone_died(*philo))
			break ;
		eat_now(philo);
		if (someone_died(*philo) || is_full(*philo))
			break ;
		sleep_now(philo);
		if (someone_died(*philo))
			break ;
		talk_now(*philo, THINK);
	}
	if (pthread_join(philo->monitor_thread, NULL) != 0)
		return (THR_JOIN_FAIL);
	return (NO_ERROR);
}
