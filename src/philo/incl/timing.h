/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:32 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/06 20:54:32 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_H
# define TIMING_H

# include <philosopher.h>

t_time_stamp	set_time(void);
long			ms_passed(t_time_stamp start);
void			custom_sleep(t_msecs ms, t_philo philo);
int				check_death_timer(t_info info);

#endif