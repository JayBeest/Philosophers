/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:43 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/14 01:06:07 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <philosopher.h>
#include <child.h>

t_time_stamp	set_time(void)
{
	t_time_stamp	time_stamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_stamp.sec = current.tv_sec;
	time_stamp.msec = current.tv_usec / 1000;
	return (time_stamp);
}

long	ms_passed(t_time_stamp start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - start.sec) * 1000 + \
		(current.tv_usec / 1000 - start.msec));
}

void	custom_sleep(t_msecs ms, t_philo philo)
{
	t_time_stamp	start;
	int				check_death_counter;

	check_death_counter = 0;
	start = set_time();
	while (ms - ms_passed(start) > 0)
	{
		usleep(INTERVAL);
		if (check_death_counter % 8 == 0 && someone_died(philo))
			break ;
		check_death_counter++;
	}
}
