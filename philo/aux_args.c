/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:03:55 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/25 08:44:36 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_numeric(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Arguments need to be numeric & positive\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	valid_args(char **argv)
{
	int	i;

	i = 1;
	if (check_numeric(argv))
		return (1);
	if (ft_atoi(argv[i]) > 200)
	{
		printf("Too many Philosophers! Maximum 200.\n");
		return (1);
	}
	while (i < 5)
	{
		if (argv[i][0] == '0')
		{
			printf("Arguments need to be higher than 0\n");
			return (1);
		}
		i++;
	}
	return (0);
}
