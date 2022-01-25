/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:09 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/06 20:54:09 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACT_H
# define ACT_H

void	eat_now(t_philo *philo);
void	sleep_now(t_philo *philo);
void	grab_forks(t_philo *philo);
void	drop_forks(t_philo philo);
void	talk_now(t_philo philo, t_message msg);

#endif