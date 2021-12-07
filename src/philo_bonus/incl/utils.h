/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:04:57 by jcorneli          #+#    #+#             */
/*   Updated: 2021/11/30 02:04:57 by jcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	ft_bzero(void *ptr, size_t n);
int		ft_isdigit(int c);
char	*ft_skipspace(char const *str);
int		ft_atoi(const char *ptr);

#endif