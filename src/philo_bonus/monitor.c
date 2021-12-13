/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:25:06 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/12 13:55:50 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>
#include <child.h>

void	kill_philos(t_info info)
{
	int i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		kill(info.philos[i].pid, SIGKILL);
		i++;
	}
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

void	start_sim(t_info *info)
{
	int	i;

	i = 0;
	info->settings.start_time = set_time();
	while (i < info->settings.num_philos)
	{
		info->philos[i].last_eaten = info->settings.start_time;
		if (sem_post(info->forks_sem) != 0)
			printf("start_sim SEMPOST FAIL\n");
		kill(info->philos[i].pid, SIGCONT);
		usleep(133);
		i++;
	}

}

void	*monitor_thread(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;

	start_sim(info);
	while (info->settings.died == 0)
	{
		usleep(500);
		if (info->settings.done_eating == info->settings.num_philos)
		{
			printf("ALL DONE EATING!!!!\n");
			return (NULL);
		}
		info->settings.died = check_death_timer(*info);
	}
	kill_philos(*info);
	talk_now(*info->philos, DIE);
	return (NULL);
}

