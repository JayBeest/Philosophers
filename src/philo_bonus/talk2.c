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
	printf("%5lu  Philosopher %2d ", time, philo.id);
	printf(PURPLE);
	printf("died\n");
	printf(WHITE);
}
