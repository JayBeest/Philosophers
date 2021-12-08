/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:40 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 14:28:26 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// if (msg == DIE)
	// {
		// printf("talk_sem_ptr=%p\n", philo.talk_sem);
		printf(WHITE);
		fun_ptr[msg](philo, time);

	// }
}

void	eat_now(t_philo *philo)
{
	philo->last_eaten = set_time();
	philo->times_eaten++;
	talk_now(*philo, EAT);
	custom_sleep(philo->settings->eat_time);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
}

void	sleep_now(t_philo *philo)
{
	talk_now(*philo, SLEEP);
	custom_sleep(philo->settings->sleep_time);
}

void	grab_forks(t_philo *philo)
{
	if (sem_wait(philo->forks_sem) == -1)
		printf("sem_wait fail ---> err=%s\n", strerror(errno));
	talk_now(*philo, R_FORK);
	sem_wait(philo->forks_sem);
	talk_now(*philo, L_FORK);
}

// void	drop_forks(t_philo philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo.settings->num_philos)
// 	{
// 		pthread_mutex_unlock(&philo.mutex->forks[i]);
// 		i++;
// 	}
// }
