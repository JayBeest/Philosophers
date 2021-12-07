/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:40 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 02:31:31 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosopher.h>
#include <timing.h>
#include <talk.h>

void	eat_now(t_philo *philo)
{
	philo->last_eaten = set_start_time();
	philo->times_eaten++;
	talk_now(*philo, EAT);
	custom_sleep(philo->settings->eat_time);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	sleep_now(t_philo *philo)
{
	talk_now(*philo, SLEEP);
	custom_sleep(philo->settings->sleep_time);
}

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		talk_now(*philo, L_FORK);
		pthread_mutex_lock(philo->right_fork);
		talk_now(*philo, R_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		talk_now(*philo, R_FORK);
		pthread_mutex_lock(philo->left_fork);
		talk_now(*philo, L_FORK);
	}
}

void	drop_forks(t_philo philo)
{
	int i;

	i = 0;
	while (i < philo.settings->num_philos)
	{
		pthread_mutex_unlock(&philo.mutex->forks[i]);
		i++;
	}
}