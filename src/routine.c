/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:28:08 by omartela          #+#    #+#             */
/*   Updated: 2024/08/11 14:31:15 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	ft_routine(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);

void    ft_print_lock(t_philo *philo)
{
    size_t  time;

    pthread_mutex_lock(&philo->program->lock);
    time = get_current_time() - philo->program->start_time;
    printf("%d %d has taken a fork\n", time, philo->id);
    pthread_mutex_unlock(&philo->program->lock);
}

void    ft_wait(t_philo *philo)
{
    
}

void    ft_eat(t_philo *philo)
{
    size_t  time;
    pthread_mutex_lock(philo->l_fork);
    ft_print_lock(philo);
    pthread_mutex_lock(philo->r_fork);
    ft_print_lock(philo);
    time = get_current_time() - philo->program->start_time;
    printf("%d, %d is eating\n", time, philo->id);
}