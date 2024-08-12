/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:28:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/12 12:54:07 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static void	ft_check_starvation(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->lock);
	if (get_current_time() - philo->last_eat > philo->program->die_time)
	{
		printf("%zu, %d, has died\n", get_current_time(), philo->id);
		philo->program->philo_dead = 1;
	}
	pthread_mutex_unlock(&philo->program->lock);
}

static void	ft_eat(t_philo *philo)
{
	size_t	time;

	ft_check_starvation(philo);
	pthread_mutex_lock(philo->l_fork);
	ft_print_lock(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print_lock(philo, "has taken a fork");
	time = get_current_time() - philo->program->start_time;
	printf("%zu, %d is eating\n", time, philo->id);
	philo->last_eat = time;
	ft_wait(philo, philo->program->eat_time);
	philo->no_eaten += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static	void	ft_sleep(t_philo *philo)
{
	size_t	time;

	ft_print_lock(philo, "is sleeping");
	ft_wait(philo, philo->program->sleep_time);
}

static	void	ft_thinking(t_philo *philo)
{
	ft_print_lock(philo, "is thinking");
}

void	ft_routine(t_philo *philo)
{
	/// put some better condition than 1 maybe checking some flag from program struct
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_thinking(philo);
	}
}
