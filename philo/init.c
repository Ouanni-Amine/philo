/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:33:05 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/17 21:15:39 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_init(pthread_mutex_t *forks, t_philo *philos, t_shared *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % data->philo_num];
		philos[i].shared_data = data;
		i++;
	}
}

int	forks_init(pthread_mutex_t *forks, t_shared *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (0);
		mutex_manager(&forks[i], 0);
		i++;
	}
	return (1);
}

int	init(t_shared *data, t_philo **philos, pthread_t **philo_thread)
{
	pthread_mutex_t	*forks;

	forks = ft_malloc(sizeof(pthread_mutex_t) * data->philo_num);
	*philos = ft_malloc(sizeof(t_philo) * data->philo_num);
	*philo_thread = ft_malloc(sizeof(pthread_t) * data->philo_num);
	if (!forks || !*philos || !*philo_thread)
		return (0);
	if (!forks_init(forks, data))
		return (0);
	if (pthread_mutex_init(&data->rip_mutex, NULL))
		return (0);
	mutex_manager(&data->rip_mutex, 0);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (0);
	mutex_manager(&data->meal_mutex, 0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	mutex_manager(&data->print_mutex, 0);
	philos_init(forks, *philos, data);
	return (1);
}
