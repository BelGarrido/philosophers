/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:24 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/01 13:50:44 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	neg;
	int	number;

	i = 0;
	neg = 1;
	number = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s [i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			neg = -neg;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		number = number * 10 + s[i] - '0';
		i++;
	}
	return (number * neg);
}

int	check_value(int value, int min, int max, char *msg)
{
	if (value < min || (max > 0 && value > max))
	{
		fprintf(stderr, "Error: Invalid %s\n", msg);
		return (0);
	}
	return (1);
}

int	check_valid_argument(char **argv, int argc)
{
	if ((argc != 5) && (argc != 6))
	{
		fprintf(stderr, "Error: Invalid number or arguments\n");
		return (0);
	}
	if (!check_value(ft_atoi(argv[1]), 0, 200, "num_philos"))
		return (0);
	if (!check_value(ft_atoi(argv[2]), 0, -1, "time_to_die"))
		return (0);
	if (!check_value(ft_atoi(argv[3]), 1, -1, "time_to_eat"))
		return (0);
	if (!check_value(ft_atoi(argv[4]), 1, -1, "time_to_sleep"))
		return (0);
	if (argc == 6 && !check_value(ft_atoi(argv[5]), 1, -1,
			"num_of_time_each_must_eat"))
	{
		return (0);
	}
	return (1);
}
