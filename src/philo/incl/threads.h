/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:27 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 00:20:28 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

t_bool	someone_died(t_philo philo);
t_bool	is_full(t_philo philo);
void	*philo_thread(void *arg);
void	*monitor_thread(void *arg);

#endif