#ifndef ACT_H
# define ACT_H

void	talk_now(t_philo philo, t_message msg);
void	eat_now(t_philo *philo);
void	sleep_now(t_philo *philo);
void	think_now(t_philo *philo);
void	grab_forks(t_philo *philo);

#endif