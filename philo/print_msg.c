/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:58:10 by ritavasques       #+#    #+#             */
/*   Updated: 2024/05/06 12:00:35 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, int task)
{
	size_t	time;

	time = time_at_moment() - philo->data->start;
	pthread_mutex_lock(&(philo->data->print_msg));
	if (task == TAKE_FORK && !end_program(philo))
		printf(YELLOW "%ld %d has taken a fork\n" CLEAR, time,
			philo->id);
	else if (task == SLEEP && !end_program(philo))
		printf(PINK "%ld %d is sleeping\n" CLEAR, time, philo->id);
	else if (task == THINK && !end_program(philo))
		printf(PURPLE "%ld %d is thinking\n" CLEAR, time, philo->id);
	else if (task == EAT && !end_program(philo))
		printf(ORANGE "%ld %d is eating\n" CLEAR, time, philo->id);
	else if (task == DEAD)
		printf(RED "%ld %d died\n" CLEAR, time, philo->id);
	pthread_mutex_unlock(&(philo->data->print_msg));
}
