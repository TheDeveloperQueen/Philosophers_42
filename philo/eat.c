/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:14:59 by ritavasques       #+#    #+#             */
/*   Updated: 2024/05/06 11:59:13 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	print_message(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
}

static void	unlock_mutex(t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_unlock(&(philo->data->forks[fork_1].fork_mtx));
	pthread_mutex_unlock(&(philo->data->forks[fork_2].fork_mtx));
}

int	philo_eating(t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&(philo->data->forks[fork_1].fork_mtx));
	if (end_program(philo))
	{
		pthread_mutex_unlock(&(philo->data->forks[fork_1].fork_mtx));
		return (1);
	}
	print_message(philo, TAKE_FORK);
	pthread_mutex_lock(&(philo->data->forks[fork_2].fork_mtx));
	if (end_program(philo))
	{
		unlock_mutex(philo, fork_1, fork_2);
		return (1);
	}
	print_message(philo, TAKE_FORK);
	eating(philo);
	if (end_program(philo))
	{
		unlock_mutex(philo, fork_1, fork_2);
		return (1);
	}
	philo->time_last_eat = time_at_moment();
	pthread_mutex_lock(&(philo->philo_mtx));
	philo->nbr_meals++;
	pthread_mutex_unlock(&(philo->philo_mtx));
	return (unlock_mutex(philo, fork_1, fork_2), 0);
}
