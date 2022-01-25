/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:25:17 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/07 14:25:17 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TALK_H
# define TALK_H

typedef void(*t_talk_ptr)(t_philo, t_msecs);

void	say_l_fork(t_philo philo, t_msecs time);
void	say_r_fork(t_philo philo, t_msecs time);
void	say_eat(t_philo philo, t_msecs time);
void	say_sleep(t_philo philo, t_msecs time);
void	say_think(t_philo philo, t_msecs time);

#endif
