/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:28:25 by ritavasques       #+#    #+#             */
/*   Updated: 2024/05/06 10:48:10 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (t_fork *) malloc(data->n_philos * sizeof(t_fork));
	if (!data->forks)
		return (1);
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&(data->forks[i].fork_mtx), NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(data->forks[i].fork_mtx));
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	data->philos = (t_philo *) malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nbr_meals = 0;
		data->philos[i].data = data;
		data->philos[i].dead_flag = false;
		if (pthread_mutex_init(&(data->philos[i].philo_mtx), NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(data->philos[i].philo_mtx));
			free(data->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

void	parse_args(t_data *data, char **argv)
{
	data->n_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
}

int	init_data(t_data *data, char **argv)
{
	parse_args(data, argv);
	if (pthread_mutex_init(&(data->print_msg), NULL))
		return (1);
	if (pthread_mutex_init(&(data->data_mtx), NULL))
	{
		pthread_mutex_destroy(&(data->print_msg));
		return (1);
	}
	if (init_forks(data))
	{
		pthread_mutex_destroy(&(data->print_msg));
		pthread_mutex_destroy(&(data->data_mtx));
		return (1);
	}
	if (init_philo(data))
	{
		destroy_mtx(data);
		free(data->forks);
		return (1);
	}
	data->end = false;
	return (0);
}
