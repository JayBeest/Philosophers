#include <stdio.h>
#include <philosopher.h>
#include <talk.h>

void	say_die(t_philo philo, t_msecs time)
{
	printf("%5lu  Philosopher %2d ", time, philo.id);
	printf(PURPLE);
	printf("died\n");
	printf(WHITE);
}
