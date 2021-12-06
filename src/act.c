#include <philosopher.h>
#include <timing.h>

void	eat_now(t_philo *philo)
{
	philo->last_eaten = set_start_time();
	// check died?
	printf("Philo%d started eating\n", philo->id);
	custom_sleep(philo->settings->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_now(t_philo *philo)
{
	// check died?
	printf("Philo%d started sleeping\n", philo->id);
	custom_sleep(philo->settings->sleep_time);
}

void	think_now(t_philo *philo)
{
	printf("Philo%d started thinking\n", philo->id);
}

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("Philo%d picked up L-fork (forkID=%p)\n", philo->id, philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("Philo%d picked up R-fork (forkID=%p)\n", philo->id, philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("Philo%d picked up R-fork (forkID=%p)\n", philo->id, philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		printf("Philo%d picked up L-fork (forkID=%p)\n", philo->id, philo->left_fork);
	}
}
