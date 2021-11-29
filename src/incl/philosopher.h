#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define MAX_THREADS 1024

# include <pthread.h>

#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

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