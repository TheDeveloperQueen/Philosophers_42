/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:24:32 by ritavasques       #+#    #+#             */
/*   Updated: 2024/05/06 12:09:08 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mtx(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->forks[i].fork_mtx));
		i++;
	}
	pthread_mutex_destroy(&(data->print_msg));
	pthread_mutex_destroy(&(data->data_mtx));
}

static void	destroy_mtx_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->philos[i].philo_mtx));
		i++;
	}
}

void	destroy_and_free(t_data *data)
{
	destroy_mtx(data);
	destroy_mtx_philos(data);
	free(data->forks);
	free(data->philos);
	free(data);
}

void	destroy_and_free_all(t_data *data)
{
	destroy_mtx(data);
	destroy_mtx_philos(data);
	free(data->forks);
	free(data->philos);
	free(data->thrds);
	free(data);
}
