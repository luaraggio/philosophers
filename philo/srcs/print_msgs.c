/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:59:50 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/23 23:31:07 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

