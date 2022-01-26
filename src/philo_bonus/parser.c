/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:57:20 by jcorneli          #+#    #+#             */
/*   Updated: 2021/12/13 19:59:12 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>
#include <utils.h>

static t_bool	out_of_int_range(char *str)
{
	long	val;

	val = 0;
	str = ft_skipspace(str);
	while (*str)
	{
		if (val == 0)
			val = *str - 48;
		else
			val = val * 10 + (*str - 48);
		str++;
	}
	if (val > 2147483647)
		return (TRUE);
	return (FALSE);
}

static t_bool	is_int(char *str)
{
	char	*temp;

	str = ft_skipspace(str);
	temp = str;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	if (out_of_int_range(temp))
		return (FALSE);
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
	if (settings->num_philos > MAX_FILOS)
		return (FALSE);
	return (TRUE);
}
