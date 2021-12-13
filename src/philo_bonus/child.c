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

t_bool	is_full(t_philo philo, t_bool only_checking)
{

	if (philo.times_eaten != philo.settings->max_eat)
	{

		return (FALSE);
	}
	if (!only_checking)
		philo.settings->done_eating++;

	return (TRUE);
}

void	*philo_child(void *arg)
{
	t_philo	*philo;
//	struct sigaction	stop;
//
//	stop.sa_handler = &stop_and_getppid;
//	stop.sa_flags = 0;
	philo = (t_philo *)arg;
	// printf("Hey! this is philo %d with pid=%d with ppid=%d\n", philo->id, getpid(), getppid());
	while (philo->settings->max_eat == 0 || !is_full(*philo, FALSE))
	{
		grab_forks(philo);
		eat_now(philo);
		sleep_now(philo);
		talk_now(*philo, THINK);
	}
	return (NULL);
}
