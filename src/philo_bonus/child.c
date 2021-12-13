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

t_bool	noone_died(t_philo philo)
{
	if (sem_trywait(philo.died_sem) == 0)
	{
		sem_post(philo.died_sem);
		return (FALSE);
	}
	return (TRUE);
}

t_err	philo_child(t_philo *philo)
{
	// printf("Hey! this is philo %d with pid=%d with ppid=%d\n", philo->id, getpid(), getppid());
	if (pthread_create(&philo->monitor_thread, NULL, &monitor_thread, philo) != 0)
		return (printf("Create_monitor_thread(philoID=%d) FAIL..\n", philo->id));
	while (!is_full(*philo))
	{
		grab_forks(philo);
		eat_now(philo);
		sleep_now(philo);
		talk_now(*philo, THINK);
	}
	pthread_join(philo->monitor_thread, NULL);
	return (NO_ERROR);
}
