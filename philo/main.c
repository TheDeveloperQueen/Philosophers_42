/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:28:02 by rivasque          #+#    #+#             */
/*   Updated: 2024/05/06 12:17:44 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc > 6 || argc < 5)
	{
		printf("Invalid number of arguments");
		return (1);
	}
	if (valid_args(argv))
		return (1);
	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, argv))
	{
		free(data);
		return (1);
	}
	if (init_threads(data))
	{
		destroy_and_free(data);
		return (1);
	}
	destroy_and_free_all(data);
	return (0);
}
