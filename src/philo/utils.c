/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:05:19 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 22:30:09 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' \
		|| c == '\r')
		return (c);
	return (0);
}

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

char	*ft_skipspace(char const *str)
{
	while (ft_isspace(*str))
		str++;
	return ((char *)str);
}

int	ft_atoi(const char *ptr)
{
	int	retv;

	retv = 0;
	ptr = ft_skipspace(ptr);
	while (*ptr)
	{
		if (retv == 0)
			retv = *ptr - 48;
		else
			retv = retv * 10 + (*ptr - 48);
		ptr++;
	}
	return (retv);
}
