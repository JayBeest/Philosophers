/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:40 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/14 01:24:30 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosopher.h>
#include <timing.h>
#include <child.h>
#include <talk.h>
#include <talk2.h>

void	talk_now(t_philo philo, t_message msg)
{
	static const t_talk_ptr	fun_ptr[6] = {
	[EAT] = say_eat,
	[SLEEP] = say_sleep,
	[THINK] = say_think,
	[L_FORK] = say_l_fork,
	[R_FORK] = say_r_fork,
	[DIE] = say_die
	};
	t_msecs					time;

	if (!someone_died(philo) || msg == DIE)
	{
		sem_wait(philo.talk_sem);
		time = passed(philo.settings->start_time, MS);
		fun_ptr[msg](philo, time);
		sem_post(philo.talk_sem);
	}
}

void	eat_now(t_philo *philo)
{
	philo->last_eaten = set_time();
	philo->times_eaten++;
	talk_now(*philo, EAT);
	custom_sleep(philo->settings->eat_time, *philo);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
}

void	sleep_now(t_philo *philo)
{
	talk_now(*philo, SLEEP);
	custom_sleep(philo->settings->sleep_time, *philo);
}

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->dead);
	if (sem_wait(philo->forks_sem) == -1)
		printf("sem_wait fail ---> philo_id=%d\n", philo->id);
	talk_now(*philo, R_FORK);
	if (sem_wait(philo->forks_sem) == -1)
		printf("sem_wait fail ---> philo_id=%d\n", philo->id);
	talk_now(*philo, L_FORK);
	pthread_mutex_unlock(&philo->mutex->dead);
}
