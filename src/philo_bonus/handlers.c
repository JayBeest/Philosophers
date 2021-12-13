#include <signal.h>
#include <philosopher.h>
#include <stdio.h>

void	handle_eat(int sig)
{
	(void)sig;
	static int	signal_counter;

	signal_counter++;
	printf("--------->EAT-SIGNAL<----------(x%d)\n", signal_counter);
}

void	handle_full(int sig)
{
	printf("--------->FULL-SIGNAL<----------\n");
	(void)sig;
}