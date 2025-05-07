/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:50:46 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/07 13:21:25 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	rip_process(t_shared *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		sem_wait(data->rip);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		kill(philos[i].pid, SIGKILL);
		waitpid(philos[i].pid, NULL, 0);
		i++;
	}
}

int	main(int c, char **v)
{
	t_philo		*philos;
	t_shared	data;

	ft_memset(&data, 0, sizeof(t_shared));
	if (!check_args(c, &data))
		return (print_error(ARG_ERROR_NUM), 1);
	if (!valid_args(v, &data))
		return (print_error(ARG_ERROR_ARG), 1);
	if (!init(&data, &philos))
		return (cleanup(philos, &data), print_error(ERROR), 1);
	if (!manage_process(&data, philos))
		return (cleanup(philos, &data), print_error(ERROR), 1);
	rip_process(&data, philos);
	cleanup(philos, &data);
}
