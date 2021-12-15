/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:43 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 04:42:08 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <philosopher.h>
#include <threads.h>

t_time_stamp	set_time(void)
{
	t_time_stamp	time_stamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_stamp.sec = current.tv_sec;
	time_stamp.usec = current.tv_usec;
	return (time_stamp);
}

long	passed(t_time_stamp start, t_time_unit time_unit)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (time_unit == US)
		return ((current.tv_sec - start.sec) * 1000000 + \
			(current.tv_usec - start.usec + 512));
	else if (time_unit == MS)
		return ((current.tv_sec - start.sec) * 1000 + \
			(current.tv_usec - start.usec) / 1000);
	return ((current.tv_sec - start.sec) + \
		(current.tv_usec - start.usec) / 1000000);
}

int	check_death_timer(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		if (!is_full(info.philos[i]) && \
			passed(info.philos[i].last_eaten, MS) > info.settings.die_time)
			return (i + 1);
		i++;
	}
	return (0);
}

void	custom_sleep(t_usecs us, t_philo philo)
{
	t_time_stamp	start;

	start = set_time();
	while (!someone_died(philo) && us - passed(start, US) > 0)
		usleep(INTERVAL);
}
