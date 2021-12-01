#ifndef TIMING_H
# define TIMING_H

# include <philosopher.h>

t_time_stamp	set_start_time(void);
long			passed(t_time_stamp start, t_time_unit time_unit);
void			sleep_now(t_msecs ms);

#endif