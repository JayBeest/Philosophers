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

void	say_l_fork(t_philo philo, t_msecs time)
{
	printf(WHITE);
	printf("%8lu  Philosopher %2d has taken a ", time, philo.id);
	printf(BLUE);
	printf("fork\n");
	printf(WHITE);
}

void	say_r_fork(t_philo philo, t_msecs time)
{
	printf(WHITE);
	printf("%8lu  Philosopher %2d has taken a ", time, philo.id);
	printf(RED);
	printf("fork\n");
	printf(WHITE);
}

void	say_eat(t_philo philo, t_msecs time)
{
	printf("%8lu  Philosopher %2d is ", time, philo.id);
	printf(GREEN);
	printf("eating\n");
	printf(WHITE);
}

void	say_sleep(t_philo philo, t_msecs time)
{
	printf("%8lu  Philosopher %2d is ", time, philo.id);
	printf(YELLOW);
	printf("sleeping\n");
	printf(WHITE);
}

void	say_think(t_philo philo, t_msecs time)
{
	printf("%8lu  Philosopher %2d is ", time, philo.id);
	printf(CYAN);
	printf("thinking\n");
	printf(WHITE);
}
