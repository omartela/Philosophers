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

static void	ft_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->l_fork);
	ft_print_lock(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print_lock(philo, "has taken a fork");
	pthread_mutex_lock(&philo->program->lock);
	time = get_current_time() - philo->program->start_time;
	printf("%zu, %d is eating\n", time, philo->id);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->program->lock);
	ft_wait(philo->program->eat_time);
	philo->no_eaten += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static	void	ft_sleep(t_philo *philo)
{
	ft_print_lock(philo, "is sleeping");
	ft_wait(philo->program->sleep_time);
}

static int	ft_check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->lock);
		printf("check stop returns 1 \n");
		return (1);
	}
	pthread_mutex_unlock(&philo->program->lock);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_wait(10);
	while (!ft_check_stop(philo))
	{
		printf("starting routine..\n");
		ft_eat(philo);
		ft_sleep(philo);
		ft_print_lock(philo, "is thinking");
	}
	return (philo);
}
