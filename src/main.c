/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:57:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/09 14:27:55 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int ac, char **argv)
{
	t_program	program;

	memset(&program, 0, sizeof(t_program));
	ft_parseinput(&program, argv, ac);
}
