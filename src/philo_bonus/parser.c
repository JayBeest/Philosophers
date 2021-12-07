
#include <philosopher.h>
#include <utils.h>

static t_bool	is_int(char *str)
{
	str = ft_skipspace(str);
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_bool	parse_input(int argc, char **argv, t_settings *settings)
{
	if (is_int(argv[1]))
		settings->num_philos = ft_atoi(argv[1]);
	else
		return (FALSE);
	if (is_int(argv[2]))
		settings->die_time = ft_atoi(argv[2]);
	else
		return (FALSE);
	if (is_int(argv[3]))
		settings->eat_time = ft_atoi(argv[3]);
	else
		return (FALSE);
	if (is_int(argv[4]))
		settings->sleep_time = ft_atoi(argv[4]);
	else
		return (FALSE);
	if (argc == 6 && is_int(argv[5]))
		settings->max_eat = ft_atoi(argv[5]);
	else if (argc == 6)
		return (FALSE);
	return (TRUE);
}