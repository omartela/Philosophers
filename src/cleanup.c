/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:03:45 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 14:12:04 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < program->no_philos)
		pthread_mutex_destroy(&program->forks[i++]);
	phtread_mutex_destroy(&program->lock);
	free(program->philos);
}
