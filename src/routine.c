/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:28:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/15 22:05:54 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static int	ft_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->l_fork);
	ft_print_lock(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print_lock(philo, "has taken a fork");
	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->lock);
		return (1);
	}
	time = get_current_time() - philo->program->start_time;
	printf("%zu %d is eating\n", time, philo->id);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->program->lock);
	if (ft_wait(philo->program->eat_time, philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	philo->no_eaten += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static	int	ft_sleep(t_philo *philo)
{
	ft_print_lock(philo, "is sleeping");
	if (ft_wait(philo->program->sleep_time, philo))
		return (1);
	return (0);
}


void	*ft_routine(void *arg)
{
	t_philo	*philo;

	// add separate case for only one philosopher because it should still be a thread.
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
	{
		ft_print_lock(philo, "is thinking");
		ft_wait(philo->program->eat_time / 2, philo);
	}
	while (!ft_check_stop(philo))
	{
		if (ft_eat(philo))
			break;
		if (ft_sleep(philo))
			break;
		if (!ft_check_stop(philo))
			ft_print_lock(philo, "is thinking");
		else
			break;
	}
	return (philo);
}
