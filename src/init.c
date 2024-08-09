/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:06:39 by omartela          #+#    #+#             */
/*   Updated: 2024/08/09 14:42:31 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	ft_init_error(char *s)
{
	printf("Error: %s \n", s);
	exit(1);
}

void	ft_init_philo(t_program *program)
{

}

void	ft_init_philos(t_program *program)
{
	program->philos = malloc(program->no_philos * sizeof(t_philo));
	if (!program->philos)
		ft_init_error("Initializing array of philosophers structs failed");
	ft_init_philo(program);
}

void	ft_init_mutexes(t_program *program)
{

}

void	ft_init(t_program *program)
{
	ft_init_philos(program);
	ft_init_mutexes(program);
}
