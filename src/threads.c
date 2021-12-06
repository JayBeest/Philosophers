#include <philosopher.h>
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

void	*monitor_thread(void *arg)
{
	t_info	*info;

	info = (t_info*)arg;
	while (info->settings->died == FALSE)
	{
		info->settings->died = check_death_timer()
	}
	return (NULL);
}