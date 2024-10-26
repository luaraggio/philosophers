/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:59:50 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/25 21:11:12 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

•Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
*/

void	my_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		my_putchar_fd(str[i], 2);
		i++;
	}
}
