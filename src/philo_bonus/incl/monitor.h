#ifndef MONITOR_H
# define MONITOR_H

void	*child_monitor_thread(void *arg);
void	start_sim(t_info *info);
t_bool	is_full(t_philo philo);

#endif
