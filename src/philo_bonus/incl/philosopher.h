/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:49 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/15 04:12:00 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <semaphore.h>

# define INTERVAL 512
# define MONITORING_INTERVAL 2048

typedef long	t_secs;
typedef long	t_msecs;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_err
{
	NO_ERROR,
	SIGACT_FAIL,
	THR_JOIN_FAIL,
	SEM_FAIL,
	MUTEX_FAIL,
	MALLOC_FAIL
}			t_err;

typedef enum e_message
{
	EAT,
	SLEEP,
	THINK,
	L_FORK,
	R_FORK,
	DIE
}			t_message;

typedef struct s_time_stamp
{
	t_secs	sec;
	t_msecs	msec;
}			t_time_stamp;

typedef struct s_mutex
{
	pthread_mutex_t	dead;
	pthread_mutex_t	full;
}			t_mutex;

typedef struct s_settings
{
	int				num_philos;
	t_msecs			die_time;
	t_msecs			eat_time;
	t_msecs			sleep_time;
	int				max_eat;
	t_time_stamp	start_time;
	int				nr_philos_full;
	int				died;
}			t_settings;

typedef struct s_philo
{
	int				id;
	int				pid;
	int				times_eaten;
	t_time_stamp	last_eaten;
	pthread_t		monitor_thread;
	t_settings		*settings;
	t_mutex			*mutex;
	sem_t			*forks_sem;
	sem_t			*talk_sem;
	sem_t			*died_sem;
	sem_t			*first_dying;
}			t_philo;

typedef struct s_info
{
	sem_t			*forks_sem;
	sem_t			*talk_sem;
	sem_t			*died_sem;
	sem_t			*can_talk_death_sem;
	t_settings		settings;
	pthread_t		monitor;
	t_philo			*philos;
	t_mutex			mutex;
}			t_info;

#endif