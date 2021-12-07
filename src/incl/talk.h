#ifndef TALK_H
# define TALK_H

# define BLACK "\033[0;30m"
# define RED  "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef void(*t_talk_ptr)(t_philo, t_msecs);

void	talk_now(t_philo philo, t_message msg);

#endif
