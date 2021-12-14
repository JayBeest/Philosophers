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
#include <philosopher.h>
#include <talk.h>

void	say_die(t_philo philo, t_msecs time)
{
	printf(WHITE);
	printf("%5lu  Philosopher %2d ", time, philo.settings->died);
	printf(PURPLE);
	printf("died\n");
	printf(WHITE);
}

void	single_philo(t_philo philo)
{
	printf(WHITE);
	printf("%5lu  Philosopher %2d has taken a ", 0ul, 1);
	printf(RED);
	printf("fork\n");
	printf(WHITE);
	usleep(philo.settings->die_time * 1000);
	printf("%5lu  Philosopher %2d ", philo.settings->die_time + 1, 1);
	printf(PURPLE);
	printf("died\n");
	printf(WHITE);
}
