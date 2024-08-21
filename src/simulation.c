/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:12:13 by omartela          #+#    #+#             */
/*   Updated: 2024/08/16 10:35:46 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static void	ft_check_starvation(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->program->lock);
	if (philo->last_eat && philo->program->philo_dead != 1)
	{
		time = get_current_time() - philo->program->start_time;
		if (time - philo->last_eat > philo->program->die_time)
		{
			printf("%zu %d has died\n", time, philo->id);
			philo->program->philo_dead = 1;
		}
	}
	pthread_mutex_unlock(&philo->program->lock);
}

static void	ft_check_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
		ft_check_starvation(&program->philos[i++]);
}

static	int	ft_check_conditions(t_program *program)
{
	int	philo_dead;
	int	no_full;
	int	error_exit;
	int	no_philos;

	ft_check_philos(program);
	pthread_mutex_lock(&program->lock);
	philo_dead = program->philo_dead;
	no_full = program->no_full;
	error_exit = program->error_exit;
	no_philos = program->no_philos;
	pthread_mutex_unlock(&program->lock);
	if (philo_dead)
		return (1);
	if (no_full == no_philos)
	{
		pthread_mutex_lock(&program->lock);
		printf("philos full \n");
		pthread_mutex_unlock(&program->lock);
		return (1);
	}
	if (error_exit)
	{
		pthread_mutex_lock(&program->lock);
		printf("error_exit \n");
		pthread_mutex_unlock(&program->lock);
		return (1);
	}
	return (0);
}

void	ft_monitor_simulation(t_program *program)
{
	while (1)
	{
		if (ft_check_conditions(program))
		{
			pthread_mutex_lock(&program->lock);
			program->stop = 1;
			pthread_mutex_unlock(&program->lock);
			break;
		}
	}
	ft_join_threads(program);
	ft_cleanup(program);
}

void	ft_start_simulation(t_program *program)
{
	int	i;

	program->start_time = get_current_time();
	if (program->no_philos == 1)
	{
		printf("%zu, %d has taken a fork\n", get_current_time() - program->start_time, 1);
		ft_wait(program->die_time, &program->philos[0]);
		printf("%zu, %d has died\n", get_current_time() - program->start_time, 1);
		ft_cleanup(program);
		exit(0);
	}
	i = 0;
	while (i < program->no_philos)
	{
		if (pthread_create(&program->philos[i].t, NULL, \
			&ft_routine, (void *)&program->philos[i]))
		{
			ft_cleanup(program);
			ft_error("Failed to create thread");
		}
		i++;
	}
}
