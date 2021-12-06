/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:40 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/06 20:54:40 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosopher.h>
#include <timing.h>

void	talk_now(t_philo philo, t_message msg)
{
	t_msecs	time;

	time = passed(philo.settings->start_time, MS);
	pthread_mutex_lock(&philo.mutex->talk);
	pthread_mutex_lock(&philo.mutex->dead);
	if (msg == FORK && philo.settings->died == 0)
		printf("%lu Philosopher %d has taken a fork\n", time, philo.id);
	else if (msg == EAT && philo.settings->died == 0)
		printf("%lu Philosopher %d is eating (x%d)\n", time, philo.id, \
			philo.times_eaten + 1);
	else if (msg == SLEEP && philo.settings->died == 0)
		printf("%lu Philosopher %d is sleeping\n", time, philo.id);
	else if (msg == THINK && philo.settings->died == 0)
		printf("%lu Philosopher %d is thinking\n", time, philo.id);
	else if (msg == DIE)
		printf("%lu Philosopher %d died\n", time, philo.settings->died);
	pthread_mutex_unlock(&philo.mutex->dead);
	pthread_mutex_unlock(&philo.mutex->talk);
}

void	eat_now(t_philo *philo)
{
	philo->last_eaten = set_start_time();
	philo->last_action = philo->last_eaten;
	talk_now(*philo, EAT);
	custom_sleep(philo->settings->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_now(t_philo *philo)
{
	philo->last_action = set_start_time();
	talk_now(*philo, SLEEP);
	custom_sleep(philo->settings->sleep_time);
}

void	think_now(t_philo *philo)
{
	philo->last_action = set_start_time();
	talk_now(*philo, THINK);
}

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->last_action = set_start_time();
		talk_now(*philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		philo->last_action = set_start_time();
		talk_now(*philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->last_action = set_start_time();
		talk_now(*philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		philo->last_action = set_start_time();
		talk_now(*philo, FORK);
	}
}
