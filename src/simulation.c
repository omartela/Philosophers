/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:12:13 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 17:51:48 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	lock_mutex(t_program *program, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
	{
		printf("Locking mutex failed");
		program->error_exit = 1;
	}
}

void	unlock_mutex(t_program *program, pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
	{
		printf("Unlocking mutex failed");
		program->error_exit = 1;
	}
}

int	check_conditions(t_program *program)
{
	int	philo_dead;
	int	no_full;
	int	error_exit;
	// make lock because accessing shared resources
	// lock and unlock can fail
	// so make own function to handle locking and unlocking
	lock_mutex(program, &program->lock);
	philo_dead = program->philo_dead;
	no_full = program->no_full;
	error_exit = program->error_exit;
	unlock_mutex(program, &program->lock);
	if (philo_dead)
		return (1);
	if (no_full == program->no_philos)
		return (1);
	if (error_exit)
		return (1);
}

void	ft_monitor_simulation(t_program *program)
{
	while (1)
	{
		if (check_conditions(program))
		{
			ft_cleanup(program);
			return ;
		}
	}
}

void	ft_start_simulation(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
	{
		if (pthread_create(&program->philos[i].t, NULL, &ft_routine, &program->philos[i]))
		{
			ft_cleanup(program);
			ft_error("Failed to create thread");
		}
		i++;
	}
}
