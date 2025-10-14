/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarri <anagarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:24 by anagarri          #+#    #+#             */
/*   Updated: 2025/10/14 12:37:25 by anagarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' && !str[1])
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	int		i;
	int		neg;
	long	number;

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
	if (number > INT_MAX)
		return (0);
	return (number * neg);
}

int	check_value(char *value_str, int min, int max, char *msg)
{
	int	value;

	if (!ft_isnum(value_str))
	{
		fprintf(stderr, "Error: Invalid %s\n", msg);
		return (0);
	}
	value = ft_atoi(value_str);
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
	if (argv[1] && argv[2] && argv[3] && argv[4])
	{
		if (!check_value(argv[1], 1, 200, "num_philos"))
			return (0);
		if (!check_value(argv[2], 1, -1, "time_to_die"))
			return (0);
		if (!check_value(argv[3], 1, -1, "time_to_eat"))
			return (0);
		if (!check_value(argv[4], 1, -1, "time_to_sleep"))
			return (0);
	}
	if (argc == 6 && argv[5] && !check_value(argv[5], 1, -1,
			"num_of_time_each_must_eat"))
	{
		return (0);
	}
	return (1);
}
