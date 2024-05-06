/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:28:43 by rivasque          #+#    #+#             */
/*   Updated: 2024/05/06 12:11:30 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->thrds[i], NULL);
		i++;
	}
	pthread_mutex_lock(&(data->data_mtx));
	data->end = true;
	pthread_mutex_unlock(&(data->data_mtx));
	pthread_join(data->monitor, NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->thrds = (pthread_t *) malloc(data->n_philos * sizeof(pthread_t));
	if (!data->thrds)
		return (1);
	if (data->n_philos == 1)
	{
		if (pthread_create(&(data->thrds[0]), NULL, rt, &(data->philos[0])))
			return (free(data->thrds), 1);
	}
	else
	{
		while (i < data->n_philos)
		{
			if (pthread_create(&(data->thrds[i]), NULL, routine,
					&(data->philos[i])))
				return (free(data->thrds), 1);
			i++;
		}
	}
	if (pthread_create(&(data->monitor), NULL, routine_monitor, data))
		return (free(data->thrds), 1);
	join_threads(data);
	return (0);
}
