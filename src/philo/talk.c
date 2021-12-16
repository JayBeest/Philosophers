/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:25:04 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 14:25:29 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosopher.h>
#include <talk.h>
#include <ansi_color_codes.h>

void	say_l_fork(t_philo philo, t_msecs time)
{
	printf(WHT);
	printf(WHT "%6lu  " RESET, time);
	printf("Philosopher " WHT "%3d " RESET "has taken a ", philo.id);
	printf(UBLU "fork\n" RESET);
}

void	say_r_fork(t_philo philo, t_msecs time)
{
	printf(WHT);
	printf(WHT "%6lu  " RESET, time);
	printf("Philosopher " WHT "%3d " RESET "has taken a ", philo.id);
	printf(URED "fork\n" RESET);
}

void	say_eat(t_philo philo, t_msecs time)
{
	printf(WHT "%6lu  " RESET, time);
	printf("Philosopher " WHT "%3d " RESET "is ", philo.id);
	printf(UGRN "eating\n" RESET);
}

void	say_sleep(t_philo philo, t_msecs time)
{
	printf(WHT "%6lu  " RESET, time);
	printf("Philosopher " WHT "%3d " RESET "is ", philo.id);
	printf(UCYN "sleeping\n" RESET);
}

void	say_think(t_philo philo, t_msecs time)
{
	printf(WHT "%6lu  " RESET, time);
	printf("Philosopher " WHT "%3d " RESET "is ", philo.id);
	printf(UYEL "thinking\n" RESET);
}
