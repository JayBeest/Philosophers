#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define MAX_THREADS 1024

# include <pthread.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_timing
{
	long int	sec;
	int			usec;
}			t_timing;

typedef struct s_mutex
{
	pthread_mutex_t	forks[MAX_THREADS];
	pthread_mutex_t	dead;
}			t_mutex;

typedef struct s_philos
{
	int			id;
	pthread_t	thread;
}			t_philos;

typedef struct s_info
{
	t_philos	philos[MAX_THREADS];
	t_mutex		mutex;
	t_timing	start_time;
	int			philo_num;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			max_eat;
}			t_info;

#endif