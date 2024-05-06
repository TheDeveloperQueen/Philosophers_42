/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:47:16 by rivasque          #+#    #+#             */
/*   Updated: 2024/05/06 12:06:10 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_at_moment(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

void	ft_usleep(size_t millesecons)
{
	size_t	start;

	start = time_at_moment();
	while ((time_at_moment() - start) < millesecons)
		usleep (200);
}

bool	end_program(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&(philo->data->data_mtx));
	status = philo->data->end;
	pthread_mutex_unlock(&(philo->data->data_mtx));
	if (status)
		return (status);
	return (philo_dead(philo));
}
