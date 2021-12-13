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

void	start_sim(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		if (sem_post(info->forks_sem) != 0)
			printf("start_sim SEMPOST FAIL\n");
		kill(info->philos[i].pid, SIGCONT);
		usleep(133);
		i++;
	}
}

int	check_death_timer(t_philo philo)
{
	if (passed(philo.last_eaten, MS) > philo.settings->die_time)
	{
		sem_post(philo.died_sem);
		sem_post(philo.died_sem);
		return (1);
	}
	return (0);
}

void	*child_monitor_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->settings->died == 0)
	{
		usleep(INTERVAL);
		if (is_full(*philo) || someone_died(*philo))
		{
			return (NULL);
		}
		pthread_mutex_lock(&philo->mutex->dead);
		philo->settings->died = check_death_timer(*philo);
		pthread_mutex_unlock(&philo->mutex->dead);
	}
	talk_now(*philo, DIE);
	return (NULL);
}
