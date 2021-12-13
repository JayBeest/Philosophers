/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:55:36 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/08 22:29:20 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>
#include <signal.h>

#include <stdio.h>

// t_bool	noone_died(t_philo philo)
// {
// 	// pthread_mutex_lock(&philo.mutex->dead);
// 	if (philo.settings->died)
// 	{
// 		// pthread_mutex_unlock(&philo.mutex->dead);
// 		return (FALSE);
// 	}
// 	// pthread_mutex_unlock(&philo.mutex->dead);
// 	return (TRUE);
// }








