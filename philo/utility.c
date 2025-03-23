/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:06:29 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/17 21:19:20 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philos)
{
	pthread_mutex_lock(&philos->shared_data->rip_mutex);
	if (philos->shared_data->rip || philos->shared_data->full)
	{
		pthread_mutex_unlock(&philos->shared_data->rip_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->shared_data->rip_mutex);
	return (0);
}

void	print_status(t_philo *philos, char *message, char *color, int rip)
{
	long long	time;

	pthread_mutex_lock(&philos->shared_data->print_mutex);
	if (rip && ft_strcmp(message, "is died"))
	{
		pthread_mutex_unlock(&philos->shared_data->print_mutex);
		return ;
	}
	time = get_elapsed_time(philos->shared_data->start);
	printf("%s%lld %ld %s%s\n", color, time, philos->philo_id, message, RESET);
	pthread_mutex_unlock(&philos->shared_data->print_mutex);
}

void	ft_usleep(long long time_ms, int rip)
{
	long long	start;

	start = get_time_ms();
	while (!rip && get_elapsed_time(start) < time_ms)
		usleep(50);
}

int	mutex_manager(pthread_mutex_t *mutex, int flag)
{
	static pthread_mutex_t	*mutex_lst[203];
	static int				i;
	int						j;
	int						res;

	j = 0;
	res = 1;
	if (!flag)
		mutex_lst[i++] = mutex;
	else
	{
		while (j < i)
		{
			if (pthread_mutex_destroy(mutex_lst[j]))
				res = 0;
			j++;
		}
	}
	return (res);
}

void	cleanup(void)
{
	int	res;

	res = mutex_manager(NULL, 1);
	if (!res)
		print_error(ERROR_MUTEX);
	ft_free(NULL, 1);
}
