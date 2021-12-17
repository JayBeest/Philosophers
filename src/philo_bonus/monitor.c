/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:25:06 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/13 20:08:40 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>
#include <child.h>

t_bool	is_full(t_philo philo)
{
	if (philo.settings->max_eat == 0)
		return (FALSE);
	else if (philo.times_eaten != philo.settings->max_eat)
		return (FALSE);
//	printf("----->PHILO %d FULL<-----\n", philo.id);
	return (TRUE);
}

void	kill_philos(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		kill(info.philos[i].pid, SIGKILL);
		i++;
	}
}

//void	start_sim(t_info *info)
//{
//	int	i;
//
//	i = 0;
//	while (i < info->settings.num_philos)
//	{
//		if (sem_post(info->forks_sem) != 0)
//			printf("start_sim SEMPOST FAIL\n");
//		kill(info->philos[i].pid, SIGCONT);
//		usleep(25);
//		i++;
//	}
////	info->settings.start_time = set_time();
//}

int	check_death_timer(t_philo philo)
{
	int	i;

	if (ms_passed(philo.last_eaten) > philo.settings->die_time)
	{
		i = 0;
		while (i < philo.settings->num_philos)
		{
//			printf("add died_sem\n");
			sem_post(philo.died_sem);
			i++;
		}
		return (1);
	}
	return (0);
}

void	drop_forks(t_philo philo)
{
	int	i;

	i = 0;
	while (i < philo.settings->num_philos)
	{
		sem_post(philo.forks_sem);
		i++;
	}
}

void	*child_monitor_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// philo->settings->start_time = set_time();
	while (!someone_died(*philo))
	{
		usleep(MONITORING_INTERVAL);
		if (is_full(*philo) || someone_died(*philo))
			return (NULL);
		pthread_mutex_lock(&philo->mutex->dead);
		philo->settings->died = check_death_timer(*philo);
		pthread_mutex_unlock(&philo->mutex->dead);
	}
	if (sem_trywait(philo->first_dying) == 0)
	{
		talk_now(*philo, DIE);
		drop_forks(*philo);
	}
	return (NULL);
}
