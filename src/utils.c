/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:05:19 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 02:05:19 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

void	ft_bzero(void *ptr, size_t n)
{
	while (n > 0)
	{
		*(char *)ptr = 0;
		ptr++;
		n--;
	}
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' \
		|| c == '\r')
		return (c);
	return (0);
}

char	*ft_skipspace(char const *str)
{
	while (ft_isspace(*str))
		str++;
	return ((char *)str);
}

int	ft_atoi(const char *ptr)
{
	int	multip;
	int	retv;

	retv = 0;
	multip = 1;
	while (*ptr)
	{
		if (retv == 0)
			retv = *ptr - 48;
		else
			retv = retv * 10 + (*ptr - 48);
		ptr++;
	}
	return (retv * multip);
}