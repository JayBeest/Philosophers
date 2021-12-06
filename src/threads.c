#include <unistd.h>
#include <philosopher.h>
#include <timing.h>
#include <act.h>

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	// size_t 		us_since_start;

	philo = (t_philo *)arg;
	// us_since_start = passed(philo->settings->start_time, US);
	// pthread_mutex_lock(&philo->mutex->id);
	// printf("This is from thread %d ====>", philo->id);
	// printf("Started after %zu us\n", us_since_start);
	// pthread_mutex_unlock(&philo->mutex->id);
	while (philo->settings->max_eat == 0 || philo->times_eaten < philo->settings->max_eat)
	{
		grab_forks(philo);
		eat_now(philo);
		philo->times_eaten++;
		sleep_now(philo);
		think_now(philo);	
	}
	return (NULL);
}

int	check_death_timer(t_info info)
{
	int	i;

	i = 0;
	while (i < info.settings.num_philos)
	{
		if ((info.settings.max_eat == 0 || info.philo[i].times_eaten < info.settings.max_eat) && passed(info.philo[i].last_eaten, MS) > info.settings.die_time)
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_info	*info;

	info = (t_info*)arg;
	while (info->settings.died == 0)
	{
		usleep(INTERVAL);
		pthread_mutex_lock(&info->mutex.dead);
		info->settings.died = check_death_timer(*info);
		pthread_mutex_unlock(&info->mutex.dead);
	}
	talk_now(*info->philo, DIE);
	return (NULL);
}