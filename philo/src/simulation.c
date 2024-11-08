/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:12:13 by omartela          #+#    #+#             */
/*   Updated: 2024/08/26 17:34:45 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static void	check_starvation(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->philo_dead != 1)
	{
		time = get_current_time() - philo->program->start_time;
		if (time - philo->last_eat > philo->program->die_time)
		{
			printf("%zu %d died\n", time, philo->id);
			philo->program->philo_dead = 1;
		}
	}
	pthread_mutex_unlock(&philo->program->lock);
}

static void	check_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
		check_starvation(&program->philos[i++]);
}

static	int	check_conditions(t_program *program)
{
	int	philo_dead;
	int	no_full;
	int	no_philos;

	check_philos(program);
	pthread_mutex_lock(&program->lock);
	philo_dead = program->philo_dead;
	no_full = program->no_full;
	no_philos = program->no_philos;
	pthread_mutex_unlock(&program->lock);
	if (philo_dead)
		return (1);
	if (no_full == no_philos)
		return (1);
	return (0);
}

void	monitor_simulation(t_program *program)
{
	while (1)
	{
		if (check_conditions(program))
		{
			pthread_mutex_lock(&program->lock);
			program->stop = 1;
			pthread_mutex_unlock(&program->lock);
			break ;
		}
	}
	join_threads(program, program->no_philos);
	cleanup(program);
}

void	start_simulation(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&program->lock);
	while (i < program->no_philos)
	{
		if (pthread_create(&program->philos[i].t, NULL, \
			&routine, (void *)&program->philos[i]))
		{
			join_threads(program, i);
			cleanup(program);
			error("Failed to create thread");
		}
		i++;
	}
	program->start_time = get_current_time();
	program->start = 1;
	pthread_mutex_unlock(&program->lock);
}
