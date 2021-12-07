#include <stdio.h>
#include <philosopher.h>
#include <threads.h>
#include <timing.h>
#include <talk.h>

static void	say_l_fork(t_philo philo, t_msecs time)
{
		printf("%5lu  Philosopher %2d has taken a ", time, philo.id);
		printf(BLUE);
		printf("fork\n");
		printf(WHITE);
}

static void	say_r_fork(t_philo philo, t_msecs time)
{
		printf("%5lu  Philosopher %2d has taken a ", time, philo.id);
		printf(RED);
		printf("fork\n");
		printf(WHITE);
}

static void	say_eat(t_philo philo, t_msecs time)
{
		printf("%5lu  Philosopher %2d is ", time, philo.id);
		printf(GREEN);
		printf("eating\n");
		printf(WHITE);
}

static void	say_sleep(t_philo philo, t_msecs time)
{
		printf("%5lu  Philosopher %2d is ", time, philo.id);
		printf(YELLOW);
		printf("sleeping\n");
		printf(WHITE);
}

static void	say_think(t_philo philo, t_msecs time)
{
		printf("%5lu  Philosopher %2d is ", time, philo.id);
		printf(CYAN);
		printf("thinking\n");
		printf(WHITE);
}

static void	say_die(t_philo philo, t_msecs time)
{
		printf("%5lu  Philosopher %2d ", time, philo.id);
		printf(PURPLE);
		printf("died\n");
		printf(WHITE);
}

void	talk_now(t_philo philo, t_message msg)
{
	static t_talk_ptr fun_ptr[6] = {
		[EAT] = say_eat,
		[SLEEP] = say_sleep,
		[THINK] = say_think,
		[L_FORK] = say_l_fork,
		[R_FORK] = say_r_fork,
		[DIE] = say_die
	};
	t_msecs	time;

	time = passed(philo.settings->start_time, MS);
	if (msg == DIE || noone_died(philo))
	{
		pthread_mutex_lock(&philo.mutex->talk);
		fun_ptr[msg](philo, time);
		pthread_mutex_unlock(&philo.mutex->talk);
	}
	// pthread_mutex_lock(&philo.mutex->dead);
	// if (msg == FORK && philo.settings->died == 0)
	// 	printf("%5lu  Philosopher %2d has taken a fork\n", time, philo.id);
	// else if (msg == EAT && philo.settings->died == 0)
	// 	printf("%5lu  Philosopher %2d is eating\n", time, philo.id);
	// else if (msg == SLEEP && philo.settings->died == 0)
	// 	printf("%5lu  Philosopher %2d is sleeping\n", time, philo.id);
	// else if (msg == THINK && philo.settings->died == 0)
	// 	printf("%5lu  Philosopher %2d is thinking\n", time, philo.id);
	// else if (msg == DIE)
	// 	printf("%5lu  Philosopher %2d died\n", time, philo.settings->died);
	// pthread_mutex_unlock(&philo.mutex->dead);
}