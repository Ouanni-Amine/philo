/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:59:07 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/12 16:43:38 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_full(t_shared *data, t_philo *philos)
{
	if (data->meals_num != -1 && philos->meals_eaten >= data->meals_num)
	{
		philos->stop = 1;
		sem_post(data->rip);
		return (1);
	}
	return (0);
}

int	check_one(t_shared *data, t_philo *philos)
{
	if (data->philo_num == 1)
	{
		ft_usleep(data->t_die);
		print_status(philos, DEAD_NOTIF, RED);
		sem_post(data->forks);
		sem_post(data->rip);
		return (1);
	}
	return (0);
}

void	eat_habit(t_shared *data, t_philo *philos)
{
	philos->last_meal = get_time_ms();
	print_status(philos, EAT_NOTIF, YELLOW);
	philos->meals_eaten++;
	philos->is_eating = 1;
	ft_usleep(data->t_eat);
	philos->is_eating = 0;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_routine(t_philo *philos)
{
	t_shared	*data;

	data = philos->shared;
	while (!philos->stop)
	{
		if (is_full(data, philos))
			return ;
		sem_wait(data->forks);
		print_status(philos, FORK_NOTIF, GREEN);
		if (check_one(data, philos))
			return ;
		sem_wait(data->forks);
		print_status(philos, FORK_NOTIF, GREEN);
		eat_habit(data, philos);
		if (philos->stop || is_full(data, philos))
			return ;
		print_status(philos, SLEEP_NOTIF, CYAN);
		ft_usleep(data->t_sleep);
		if (philos->stop || is_full(data, philos))
			return ;
		print_status(philos, THINK_NOTIF, MAGENTA);
	}
}
