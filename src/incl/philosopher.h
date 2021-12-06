/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:49 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/01 00:13:29 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>

# define INTERVAL 250

typedef long	t_secs;
typedef long	t_msecs;
typedef long	t_usecs;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_err
{
	NO_ERROR,
	MALLOC_FAIL
}			t_err;

typedef enum e_message
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIE
}			t_message;

typedef struct s_time_stamp
{
	t_secs	sec;
	t_usecs	usec;
}			t_time_stamp;

typedef enum e_time_unit
{
	S,
	MS,
	US
}			t_time_unit;

typedef struct s_settings
{
	int				num_philos;
	t_msecs			die_time;
	t_msecs			eat_time;
	t_msecs			sleep_time;
	int				max_eat;
	t_time_stamp	start_time;
	int				done_eating;
	int				died;
}			t_settings;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
	pthread_mutex_t	full;
	pthread_mutex_t	talk;
}			t_mutex;

typedef struct s_philo
{
	t_settings		*settings;
	t_mutex			*mutex;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				times_eaten;
	t_time_stamp	last_eaten;
}			t_philo;

typedef struct s_info
{
	t_mutex			mutex;
	t_settings		settings;
	pthread_t		monitor;

	t_philo			*philo;
}			t_info;

#endif