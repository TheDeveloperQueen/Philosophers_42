/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:44:35 by rivasque          #+#    #+#             */
/*   Updated: 2024/05/06 11:39:57 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_dead(t_philo *philo)
{
	bool	dead;

	if ((time_at_moment() - philo->time_last_eat) > philo->data->time_to_die)
	{
		print_message(philo, DEAD);
		pthread_mutex_lock(&(philo->philo_mtx));
		philo->dead_flag = true;
		pthread_mutex_unlock(&(philo->philo_mtx));
	}
	dead = philo->dead_flag;
	return (dead);
}

bool	check_dead(t_data *data, int i)
{
	bool	dead;

	pthread_mutex_lock(&(data->philos[i].philo_mtx));
	dead = data->philos[i].dead_flag;
	pthread_mutex_unlock(&(data->philos[i].philo_mtx));
	return (dead);
}

int	philo_full(t_philo *philo)
{
	int	is_full;

	if (philo->data->max_meals == -1)
		return (0);
	pthread_mutex_lock(&(philo->philo_mtx));
	is_full = philo->nbr_meals;
	pthread_mutex_unlock(&(philo->philo_mtx));
	return (is_full == philo->data->max_meals);
}

int	all_full(int meals, t_data *data)
{
	if (data->max_meals == -1)
		return (0);
	if (meals == data->n_philos)
	{
		pthread_mutex_lock(&(data->data_mtx));
		data->end = true;
		pthread_mutex_unlock(&(data->data_mtx));
		return (1);
	}	
	return (0);
}

void	philo_sleeping(t_philo *philo)
{
	print_message(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
}
