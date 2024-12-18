/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:57:08 by omartela          #+#    #+#             */
/*   Updated: 2024/11/04 16:08:46 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	main(int ac, char **argv)
{
	t_program	program;

	memset(&program, 0, sizeof(t_program));
	if (parseinput(&program, argv, ac))
		return (1);
	if (init(&program))
		return (1);
	start_simulation(&program);
	monitor_simulation(&program);
	return (0);
}
