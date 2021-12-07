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
#include <threads.h>
#include <timing.h>
#include <talk.h>
#include <talk2.h>

void	talk_now(t_philo philo, t_message msg)
{
	static t_talk_ptr	fun_ptr[6] = {
		[EAT] = say_eat,
		[SLEEP] = say_sleep,
		[THINK] = say_think,
		[L_FORK] = say_l_fork,
		[R_FORK] = say_r_fork,
		[DIE] = say_die
	};
	t_msecs				time;

	time = passed(philo.settings->start_time, MS);
	if (msg == DIE || noone_died(philo))
	{
		pthread_mutex_lock(&philo.mutex->talk);
		fun_ptr[msg](philo, time);
		pthread_mutex_unlock(&philo.mutex->talk);
	}
}

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
	int	i;

	i = 0;
	while (i < philo.settings->num_philos)
	{
		pthread_mutex_unlock(&philo.mutex->forks[i]);
		i++;
	}
}
