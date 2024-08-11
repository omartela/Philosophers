/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:06:39 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 13:51:43 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	ft_init_error(char *s)
{
	printf("Error: %s \n", s);
	exit(1);
}

void	ft_init_philo(t_philo *philo, t_program *program, int i)
{
	philo->program = program;
	philo->l_fork = &program->forks[i];
	philo->r_fork = &program->forks[(i + 1) % program->no_philos];
	philo->id = i + 1;
	philo->no_eaten = 0;
}

int	ft_init_mutexes(t_program *program)
{
	int	i;

	if (pthread_mutex_init(&program->lock, NULL))
		return (1);
	i = 0;
	while (i < program->no_philos)
	{
		if (pthread_mutex_init(&program->forks[i++], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&program->forks[--i]);
			pthread_mutex_destroy(&program->lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_init(t_program *program)
{
	int	i;

	i = 0;
	program->start_time = get_current_time();
	program->no_full = 0;
	program->all_full = 0;
	program->philo_dead = 0;
	program->philos = malloc(program->no_philos * sizeof(t_philo));
	if (!program->philos)
		ft_init_error("Initializing array of philosophers structs failed");
	if (ft_init_mutexes(program))
	{
		free(program->philos);
		ft_init_error("Initializing array of mutexes failed");
	}
	while (i < program->no_philos)
	{
		ft_init_philo(&program->philos[i], program, i);
		i++;
	}
}
