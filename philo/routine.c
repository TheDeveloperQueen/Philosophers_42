/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:08:31 by rivasque          #+#    #+#             */
/*   Updated: 2024/05/06 12:18:06 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, int *fork_1, int *fork_2)
{
	*fork_1 = philo->id % philo->data->n_philos;
	*fork_2 = (philo->id - 1) % philo->data->n_philos;
}

static void	set_end(t_data *data)
{
	pthread_mutex_lock(&(data->data_mtx));
	data->end = true;
	pthread_mutex_unlock(&(data->data_mtx));
}

void	*routine_monitor(void *args)
{
	t_data	*data;
	int		i;
	int		finish;
	int		full;

	finish = 1;
	data = (t_data *)args;
	while (finish)
	{
		i = 0;
		full = 0;
		while (finish && i < data->n_philos)
		{
			full += philo_full(&(data->philos[i]));
			if (check_dead(data, i))
			{
				set_end(data);
				finish = 0;
			}
			i++;
		}
		if (all_full(full, data))
			break ;
	}
	return (NULL);
}

void	*rt(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->data->start = time_at_moment();
	pthread_mutex_lock(&(philo->philo_mtx));
	philo->time_last_eat = time_at_moment();
	pthread_mutex_unlock(&(philo->philo_mtx));
	print_message(philo, TAKE_FORK);
	while (!philo_dead(philo))
		usleep(200);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;
	int		fork_1;
	int		fork_2;

	philo = (t_philo *)data;
	philo->data->start = time_at_moment();
	pthread_mutex_lock(&(philo->philo_mtx));
	philo->time_last_eat = time_at_moment();
	pthread_mutex_unlock(&(philo->philo_mtx));
	assign_forks(philo, &fork_1, &fork_2);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while (!end_program(philo))
	{
		if (philo_eating(philo, fork_1, fork_2))
			break ;
		if (philo_full(data) || end_program(philo))
			break ;
		philo_sleeping(philo);
		if (end_program(philo))
			break ;
		print_message(philo, THINK);
	}
	return (NULL);
}
