/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:33 by omartela          #+#    #+#             */
/*   Updated: 2024/08/13 12:37:02 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	ft_print_lock(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->program->lock);
	time = get_current_time() - philo->program->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->program->lock);
}

void	ft_wait(size_t ms)
{
	size_t	str;
	printf("waiting...\n");
	str = get_current_time();
	while ((get_current_time() - str) < ms)
		usleep(500);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((size_t)time.tv_sec * 1000 + time.tv_usec / 1000);
}
