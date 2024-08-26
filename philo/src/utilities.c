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
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->lock);
		return ;
	}
	time = get_current_time() - philo->program->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->program->lock);
}

int	ft_check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->lock);
	return (0);
}

int	ft_wait(size_t ms, t_philo *philo)
{
	size_t	str;

	str = get_current_time();
	while ((get_current_time() - str) < ms)
	{
		usleep(500);
		if (ft_check_stop(philo))
			return (1);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
