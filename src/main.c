/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:57:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 17:54:09 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	main(int ac, char **argv)
{
	t_program	program;

	memset(&program, 0, sizeof(t_program));
	ft_parseinput(&program, argv, ac);
	ft_start_simulation(&program);
	return (0);
}
