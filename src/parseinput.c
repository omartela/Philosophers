/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:55:06 by omartela          #+#    #+#             */
/*   Updated: 2024/08/13 22:56:42 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	ft_message(void)
{
	printf("Program should take the following arguments: \n");
	printf("Mandatory: Number of philosophers > 0 \n");
	printf("Mandatory: The time when philosopher dies\
	if he does not eat > 0 \n");
	printf("Mandatory: The time it takes to philosopher eat > 0 \n");
	printf("Mandatory: Time to sleep > 0 \n");
	printf("Optional: Number of times each philosopher\
	must eat to become full >= 0 \n");
	exit(1);
}

int	ft_str_to_int(char *str, int no_zero)
{
	long int	res;

	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == '\n')
		++str;
	if (*str == '-')
		ft_message();
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str++ - '0';
		if (res > 2147483647)
			ft_message();
	}
	if (*str || (no_zero && res == 0))
		ft_message();
	return ((int)res);
}

void	ft_parseinput(t_program *program, char **str, int ac)
{
	if (ac < 5 || ac > 6)
		ft_message();
	program->no_philos = ft_str_to_int(str[1], 1);
	program->die_time = ft_str_to_int(str[2], 1);
	program->eat_time = ft_str_to_int(str[3], 1);
	program->sleep_time = ft_str_to_int(str[4], 1);
	if (ac == 6)
		program->no_meals = ft_str_to_int(str[5], 0);
	else
		program->no_meals = -1;
}
