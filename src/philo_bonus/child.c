/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:40:05 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/10 18:00:29 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>
#include <act.h>
#include <talk.h>
#include <timing.h>
#include <monitor.h>
#include <semaphore.h>

#include <unistd.h>

t_bool	someone_died(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->dead);
	if (sem_trywait(philo.died_sem) == 0)
	{
		sem_post(philo.died_sem);
		pthread_mutex_unlock(&philo.mutex->dead);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo.mutex->dead);
	return (FALSE);
}

t_err	philo_child(t_philo *philo)
{
	// printf("Hey! this is philo %d with pid=%d with ppid=%d\n", philo->id, getpid(), getppid());
	philo->settings->start_time = set_time();
		philo->last_eaten = philo->settings->start_time;
	if (pthread_create(&philo->monitor_thread, NULL, &child_monitor_thread, philo) != 0)
		return (printf("Create_monitor_thread(philoID=%d) FAIL..\n", philo->id));
	while (!is_full(*philo))
	{
		if (someone_died(*philo))
			break ;
		grab_forks(philo);
		if (someone_died(*philo))
			break ;
		eat_now(philo);
		if (someone_died(*philo))
			break ;
		sleep_now(philo);
		if (someone_died(*philo))
			break ;
		talk_now(*philo, THINK);
	}
	if (pthread_join(philo->monitor_thread, NULL) != 0)
		return(THR_JOIN_FAIL);
	return (NO_ERROR);
}
