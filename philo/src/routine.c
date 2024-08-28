/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:28:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/28 12:52:50 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static int	ft_sleep(t_philo *philo)
{
	ft_print_lock(philo, "is sleeping");
	if (ft_wait(philo->program->sleep_time, philo))
		return (1);
	return (0);
}

static void	ft_one_philo(t_philo *philo)
{
	int	start_time;

	pthread_mutex_lock(philo->l_fork);
	start_time = philo->program->start_time;
	printf("%zu %d has taken a fork\n", get_current_time() - start_time, 1);
	ft_wait(philo->program->die_time, &philo->program->philos[0]);
	pthread_mutex_unlock(philo->l_fork);
}

static void	ft_philo_wait(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		ft_print_lock(philo, "is thinking");
		ft_wait(philo->program->eat_time / 2, philo);
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->program->lock);
	while (!philo->program->start)
		ft_wait(1, philo);
	pthread_mutex_unlock(&philo->program->lock);
	if (philo->program->no_philos == 1)
	{
		ft_one_philo(philo);
		return (philo);
	}
	ft_philo_wait(philo);
	while (!ft_check_stop(philo))
	{
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (!ft_check_stop(philo))
			ft_print_lock(philo, "is thinking");
		else
			break ;
	}
	return (philo);
}
