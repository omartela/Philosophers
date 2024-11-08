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

static void	message(void)
{
	printf("Program should take the following arguments: \n");
	printf("Mandatory: Number of philosophers > 0 \n");
	printf("Mandatory: The time when philosopher dies > 0 \n");
	printf("Mandatory: The time it takes to philosopher eat > 0 \n");
	printf("Mandatory: Time to sleep > 0 \n");
	printf("Optional: Number of times each philosopher eats >= 0 \n");
}

static char	*trim_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == '\n')
		++str;
	return (str);
}

static int	check_negative_sign(char *str, int *error)
{
	if (*str == '-')
	{
		*error = 1;
		message();
		return (1);
	}
	return (0);
}

static int	str_to_int(char *str, int no_zero, int *error)
{
	long int	res;

	res = 0;
	str = trim_whitespace(str);
	if (check_negative_sign(str, error))
		return (1);
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str++ - '0';
		if (res > 2147483647)
		{
			message();
			*error = 1;
			return (1);
		}
	}
	if (*str || (no_zero && res == 0))
	{
		message();
		*error = 1;
		return (1);
	}
	return ((int)res);
}

int	parseinput(t_program *program, char **str, int ac)
{
	int	error;

	error = 0;
	if (ac < 5 || ac > 6)
	{
		message();
		return (1);
	}
	program->no_philos = str_to_int(str[1], 1, &error);
	program->die_time = str_to_int(str[2], 1, &error);
	program->eat_time = str_to_int(str[3], 1, &error);
	program->sleep_time = str_to_int(str[4], 1, &error);
	if (ac == 6)
		program->no_meals = str_to_int(str[5], 0, &error);
	else
		program->no_meals = -1;
	if (error)
		return (1);
	return (0);
}
