/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:25:12 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 14:25:12 by jcorneli         ###   ########.fr       */
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
	printf(RED "fork\n");
	usleep(philo.settings->die_time * 1000);
	printf(WHT "%6lu  " RESET, philo.settings->die_time + 1);
	printf("Philosopher " WHT "%3d ", 1);
	printf(UMAG "died\n" RESET);
}
