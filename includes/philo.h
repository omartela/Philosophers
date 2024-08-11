/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:29:12 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 14:10:35 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	t_program		*program;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	size_t			last_eat;
	int				no_eaten;
	int				id;
	pthread_t		t;	
}	t_philo;

typedef struct s_program
{
	int				no_philos;
	t_philo			*philos;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	size_t			eat_time;
	size_t			die_time;
	size_t			sleep_time;
	size_t			start_time;
	int				no_full;
	int				all_full;
	int				philo_dead;
	int				no_meals;
}	t_program;

// parseinput.c
void	ft_parseinput(t_program *program, char **str, int ac);

// utilities.c
size_t	get_current_time(void);

// init.c

// ft_cleanup.c
void	ft_cleanup(t_program *program)


#endif