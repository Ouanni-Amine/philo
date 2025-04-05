/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:12:52 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/05 19:26:25 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_single_philo(t_philo *philos)
{
	if (philos->shared_data->philo_num == 1)
	{
		ft_usleep(philos->shared_data->t_die, should_stop(philos), philos);
		print_status(philos, DEAD_NOTIF, RED, should_stop(philos));
		pthread_mutex_lock(&philos->shared_data->rip_mutex);
		philos->shared_data->rip = 1;
		pthread_mutex_unlock(&philos->shared_data->rip_mutex);
		return (0);
	}
	return (1);
}

void	mutex_order(t_philo *philos)
{
	pthread_mutex_lock(philos->r_fork);
	print_status(philos, FORK_NOTIF, GREEN, should_stop(philos));
	if (!handle_single_philo(philos))
		return ;
	pthread_mutex_lock(philos->l_fork);
	print_status(philos, FORK_NOTIF, GREEN, should_stop(philos));
}

void	philo_eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->shared_data->meal_mutex);
	philos->last_meal = get_elapsed_time(philos->shared_data->start);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->shared_data->meal_mutex);
	print_status(philos, EAT_NOTIF, YELLOW, should_stop(philos));
	ft_usleep(philos->shared_data->t_eat, should_stop(philos), philos);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

void	think_nd_sleep(t_philo *philos)
{
	print_status(philos, SLEEP_NOTIF, CYAN, should_stop(philos));
	ft_usleep(philos->shared_data->t_sleep, should_stop(philos), philos);
	print_status(philos, THINK_NOTIF, MAGENTA, should_stop(philos));
}

void	*philo_routine(void *args)
{
	t_philo		*philos;
	t_shared	*data;

	philos = (t_philo *)args;
	data = philos->shared_data;
	if (philos->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (should_stop(philos))
			break ;
		mutex_order(philos);
		if (should_stop(philos))
		{
			pthread_mutex_unlock(philos->r_fork);
			if (data->philo_num > 1)
				pthread_mutex_unlock(philos->l_fork);
			break ;
		}
		philo_eat(philos);
		think_nd_sleep(philos);
	}
	return (NULL);
}
