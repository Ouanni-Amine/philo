/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:03:24 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/17 20:51:12 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int c, t_shared *data)
{
	if (c < 5 || c > 6)
		return (0);
	if (c == 5)
		data->meals_num = -1;
	return (1);
}

int	check_single(char *v)
{
	int	i;

	i = 0;
	if (v[i] == '+')
		i++;
	while (v[i])
	{
		if (!ft_isdigit(v[i]))
			return (0);
		i++;
	}
	return (1);
}

int	fill_args_p2(long res, t_shared *data, int i)
{
	if (i == 1)
	{
		if (res == 0 || res > 200)
			return (0);
		data->philo_num = (int)res;
	}
	else if (i >= 2 && i <= 4 && res < 60)
		return (0);
	else if (i == 2)
		data->t_die = (int)res;
	else if (i == 3)
		data->t_eat = (int)res;
	else if (i == 4)
		data->t_sleep = (int)res;
	else
	{
		if (res == 0)
			return (0);
		data->meals_num = (int)res;
	}
	return (1);
}

int	fill_args(int i, char *v, t_shared *data)
{
	int		j;
	long	res;

	j = 0;
	if (v[j] == '+')
		j++;
	while (v[j] == '0')
		j++;
	if (ft_strlen(v + j) > 10)
		return (0);
	res = ft_long_atoi(v);
	if (res > 2147483647 || res < 0)
		return (0);
	if (!fill_args_p2(res, data, i))
		return (0);
	return (1);
}

int	valid_args(char **v, t_shared *data)
{
	int	i;

	i = 1;
	while (v[i])
	{
		if (v[i][0] == '\0')
			return (0);
		if (!check_single(v[i]))
			return (0);
		if (!fill_args(i, v[i], data))
			return (0);
		i++;
	}
	return (1);
}
