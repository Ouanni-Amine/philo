/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:57:30 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/17 20:57:25 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create(pthread_t *philo_thread, t_philo *philos)
{
	int	i;

	i = 0;
	philos->shared_data->start = get_time_ms();//TODO: check return value
	while (i < philos->shared_data->philo_num)
	{
		philos[i].last_meal = philos->shared_data->start;
		if (pthread_create(&philo_thread[i], NULL, philo_routine, &philos[i]))
			return (0);
		i++;
	}
	return (1);
}

int	thread_join(pthread_t *philo_thread, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->shared_data->philo_num)
	{
		if (pthread_join(philo_thread[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
