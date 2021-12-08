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

#include <pthread.h>
#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>

#include <stdio.h>

// t_bool	noone_died(t_philo philo)
// {
// 	// pthread_mutex_lock(&philo.mutex->dead);
// 	if (philo.settings->died)
// 	{
// 		// pthread_mutex_unlock(&philo.mutex->dead);
// 		return (FALSE);
// 	}
// 	// pthread_mutex_unlock(&philo.mutex->dead);
// 	return (TRUE);
// }

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

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_eaten = set_time();
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
		usleep(500);
		printf("Philo[1] since last eaten = %ld\n", passed(info->philos[1].last_eaten, MS));
		if (info->settings.done_eating == info->settings.num_philos)
		{
			printf("ALL DONE EATING!!!!\n");
			return (NULL);
		}
		info->settings.died = check_death_timer(*info);
		if (info->settings.died > 0)
			printf("settings.died == %d\n", info->settings.died);
	}
	talk_now(*info->philos, DIE);
	return (NULL);
}
