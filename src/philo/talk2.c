/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:25:12 by jcorneli          #+#    #+#             */
/*   Updated: 2022/01/30 13:23:18 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philosopher.h>
#include <ansi_color_codes.h>

void	say_die(t_philo philo, t_msecs time)
{
	printf(WHT "%6lu  " RESET, time);
	printf("Philosopher " WHT "%3d ", philo.settings->died);
	printf(UMAG "died\n" RESET);
}

void	single_philo(t_philo philo)
{
	printf(WHT "%6lu  " RESET, 0ul);
	printf("Philosopher " WHT "%3d " RESET "has taken a ", 1);
	printf(URED "fork\n");
	usleep(philo.settings->die_time * 1000);
	printf(WHT "%6lu  " RESET, philo.settings->die_time + 1);
	printf("Philosopher " WHT "%3d ", 1);
	printf(UMAG "died\n" RESET);
}

int	say_usage_error(int return_value)
{
	printf(RED "\n   Error, wrong input\n\n" RESET);
	printf(YEL "Usage: " RESET "philo " WHT "number_of_philos time_to_die ");
	printf("time_to_eat time_to_sleep " RESET "[number_of_times_to_eat]\n\n");
	printf("     - maximum philos is 999\n");
	printf("     - time is in milliseconds\n\n");
	return (return_value);
}
