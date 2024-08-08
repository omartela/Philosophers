/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:37:39 by omartela          #+#    #+#             */
/*   Updated: 2024/08/08 13:32:07 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22)
	return (time.tv_sec * 1000 + time.tv_usec / 1000)
}

