/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:28:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/28 14:59:37 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static int	philo_sleep(t_philo *philo)
{
	print_lock(philo, "is sleeping");
	if (wait(philo->program->sleep_time, philo))
		return (1);
	return (0);
}

static void	one_philo(t_philo *philo)
{
	size_t	start_time;

	pthread_mutex_lock(philo->l_fork);
	start_time = philo->program->start_time;
	printf("%zu %d has taken a fork\n", get_current_time() - start_time, 1);
	wait(philo->program->die_time, &philo->program->philos[0]);
	pthread_mutex_unlock(philo->l_fork);
}

static void	philo_wait(t_philo *philo)
{
	int	no_philos;

	pthread_mutex_lock(&philo->program->lock);
	no_philos = philo->program->no_philos;
	pthread_mutex_unlock(&philo->program->lock);
	if (no_philos % 2 != 0)
	{
		if (philo->id % 2 != 0)
			wait(philo->program->eat_time / 2, philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->program->lock);
	while (!philo->program->start)
		wait(1, philo);
	pthread_mutex_unlock(&philo->program->lock);
	if (philo->program->no_philos == 1)
	{
		one_philo(philo);
		return (philo);
	}
	philo_wait(philo);
	while (!check_stop(philo))
	{
		if (eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (!check_stop(philo))
			print_lock(philo, "is thinking");
		else
			break ;
	}
	return (philo);
}
