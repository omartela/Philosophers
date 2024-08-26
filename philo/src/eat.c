/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:23:53 by omartela          #+#    #+#             */
/*   Updated: 2024/08/26 17:35:18 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static void	ft_check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->no_meals == philo->no_eaten)
		philo->program->no_full += 1;
	pthread_mutex_unlock(&philo->program->lock);
}

static int	grap_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print_lock(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print_lock(philo, "has taken a fork");
	if (ft_check_stop(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	size_t	time;

	if (ft_check_stop(philo))
		return (1);
	if (grap_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->program->lock);
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
	ft_check_full(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}
