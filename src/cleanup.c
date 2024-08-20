/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:03:45 by omartela          #+#    #+#             */
/*   Updated: 2024/08/13 13:35:50 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	ft_error(char *s)
{
	printf("Error: %s \n", s);
}

void	ft_join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
	{
		if (pthread_join(program->philos[i].t, NULL))
		{
			ft_cleanup(program);
			ft_error("Error when joining philo threads");
		}
		i++;
	}
}

void	ft_cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
		pthread_mutex_destroy(&program->forks[i++]);
	pthread_mutex_destroy(&program->lock);
	free(program->philos);
	free(program->forks);
}
