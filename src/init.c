#include <stdlib.h>
#include <philosopher.h>
#include <pthread.h>
#include <timing.h>
#include <utils.h>

static t_bool	init_mutexes(int num_philos, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&mutex->fork[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_mutex_init(&mutex->dead, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&mutex->id, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

 static t_err	init_philos(t_info *info)
 {
	int	i;

	i = 0;
	while (i < info->settings.num_philos)
	{
		info->philo[i].id = i + 1;
		info->philo[i].settings = &info->settings;
		info->philo[i].mutex = &info->mutex;
		if (i == 0)
		{
			info->philo[i].right_fork = &info->mutex.fork[info->settings.num_philos - 1];
			info->philo[i].left_fork = &info->mutex.fork[i];
		}
		else
		{
			info->philo[i].right_fork = &info->mutex.fork[i - 1];
			info->philo[i].left_fork = &info->mutex.fork[i];
		}
		i++;
	}
	return (NO_ERROR);
 }

t_err	init_struct(t_info *info)
{
	int	num_ph;

	num_ph = info->settings.num_philos;
	info->philo = (t_philo *)malloc(num_ph * sizeof(t_philo));
	if (!info->philo)
		return (MALLOC_FAIL);
	ft_bzero(info->philo, num_ph * sizeof(t_philo));
	info->mutex.fork = (pthread_mutex_t *)malloc(num_ph * sizeof(pthread_mutex_t));
	if (!info->mutex.fork)
		return (MALLOC_FAIL);
	ft_bzero(info->mutex.fork, num_ph * sizeof(pthread_mutex_t));
	init_mutexes(info->settings.num_philos, &info->mutex);
	init_philos(info);
	return (NO_ERROR);
}
