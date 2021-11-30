/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:49 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 02:04:49 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define MAX_THREADS 512

# include <pthread.h>

#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_time_unit
{
	S,
	MS,
	US
}			t_time_unit;

typedef struct s_settings
{
	int			num_philos;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			max_eat;
}			t_settings;

typedef struct s_time_stamp
{
	long int	sec;
	int			usec;
}			t_time_stamp;

typedef struct s_mutex
{
	pthread_mutex_t	fork[MAX_THREADS];
	pthread_mutex_t	dead;
}			t_mutex;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
}			t_philo;

typedef struct s_info
{
	t_philo			philo[MAX_THREADS];
	t_mutex			mutex;
	t_time_stamp	start_time;
	t_settings		settings;
}			t_info;

#endif