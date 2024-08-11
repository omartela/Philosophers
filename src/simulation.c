/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:12:13 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 15:02:15 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	check_conditions(t_program *program)
{
	// make lock because accessing shared resources
	// lock and unlock can fail
	// so make own function to handle locking and unlocking
	if (program->philo_dead)
		return (1);
	if (program->no_full == no_philos)
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
			/// if thread creating fails cleanup functions needs to know how many threads were
			/// successfully created so it can join them correctly.
			ft_cleanup(program);
			ft_error("Failed to create thread");
		}
		i++;
	}
}
