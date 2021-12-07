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

# define BLACK "\033[0;30m"
# define RED  "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef void(*t_talk_ptr)(t_philo, t_msecs);

void	say_l_fork(t_philo philo, t_msecs time);
void	say_r_fork(t_philo philo, t_msecs time);
void	say_eat(t_philo philo, t_msecs time);
void	say_sleep(t_philo philo, t_msecs time);
void	say_think(t_philo philo, t_msecs time);

#endif
