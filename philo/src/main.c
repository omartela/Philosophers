/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:57:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/15 17:09:37 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	main(int ac, char **argv)
{
	t_program	program;

	memset(&program, 0, sizeof(t_program));
	if (ft_parseinput(&program, argv, ac))
		return (1);
	ft_init(&program);
	ft_start_simulation(&program);
	ft_monitor_simulation(&program);
	return (0);
}
