/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:03:45 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 17:53:47 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	ft_error(char *s)
{
	printf("Error: %s \n", s);
	exit(1);
}

void	ft_cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
		pthread_mutex_destroy(&program->forks[i++]);
	pthread_mutex_destroy(&program->lock);
	free(program->philos);
}
