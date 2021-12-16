/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:25:12 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 03:38:47 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philosopher.h>
// #include <talk.h>
#include <ansi_color_codes.h>

void	say_die(t_philo philo, t_msecs time)
{
	printf(WHT "%8lu  " RESET, time);
	// printf(RESET);
	printf("Philosopher " WHT "%3d ", philo.settings->died);
	// printf(MAG);
	printf(UMAG "died\n" RESET);
	// printf(WHT);
}

void	single_philo(t_philo philo)
{
	// printf(WHT);
	printf(WHT "%8lu  " RESET, 0ul);
	// printf(RESET);
	printf("Philosopher " WHT "%3d " RESET "has taken a ", 1);
	// printf(RED);
	printf(RED "fork\n");
	usleep(philo.settings->die_time * 1000);
	// printf(WHT);
	printf(WHT "%8lu  " RESET, philo.settings->die_time + 1);
	// printf(RESET);
	printf("Philosopher " WHT "%3d ", 1);
	// printf(MAG);
	printf(UMAG "died\n" RESET);
	// printf(WHT);
}
