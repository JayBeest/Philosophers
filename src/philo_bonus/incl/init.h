/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:54:15 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/08 23:23:15 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

t_err	init_struct(t_info *info);
t_err	init_signal(void);
t_err	init_mutexes(t_mutex *mutex);

#endif