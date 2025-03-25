/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:54:06 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/17 20:40:54 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philos, t_shared *data)
{
	int			i;
	long long	last_meal;
	long long	current;

	i = 0;
	pthread_mutex_lock(&data->rip_mutex);
	while (i < data->philo_num && !data->rip)
	{
		pthread_mutex_lock(&data->meal_mutex);
		last_meal = philos[i].last_meal;
		current = get_elapsed_time(data->start);//TODO: check return value
		pthread_mutex_unlock(&data->meal_mutex);
		if (!data->rip && current - last_meal >= data->t_die)
		{
			print_status(&philos[i], DEAD_NOTIF, RED, data->rip);
			data->rip = 1;
		}
		if (data->rip)
			break ;
		i++;
	}
	pthread_mutex_unlock (&data->rip_mutex);
}

void	check_meals(t_philo *philos, t_shared *data)
{
	int	i;

	i = 0;
	if (data->meals_num == -1)
		return ;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->philo_num && philos[i].meals_eaten >= data->meals_num)
		i++;
	pthread_mutex_unlock(&data->meal_mutex);
	if (i == data->philo_num)
	{
		pthread_mutex_lock(&data->rip_mutex);
		data->full = 1;
		pthread_mutex_unlock(&data->rip_mutex);
	}
}

void	monitor(t_philo *philos)
{
	t_shared	*data;

	data = philos->shared_data;
	while (1)
	{
		if (should_stop(philos))
			break ;
		check_death(philos, data);
		check_meals(philos, data);
		usleep(1000);
	}
}
