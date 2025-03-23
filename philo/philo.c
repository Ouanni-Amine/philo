/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:14 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/22 14:53:18 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
}

int	main(int c, char **v)
{
	t_shared	data;
	t_philo		*philos;
	pthread_t	*philo_thread;

	ft_memset(&data, 0, sizeof(t_shared));
	if (!check_args(c, &data))
		return (print_error(ARG_ERROR_NUM), 1);
	if (!valid_args(v, &data))
		return (print_error(ARG_ERROR_ARG), 1);
	if (!init(&data, &philos, &philo_thread))
		return (cleanup(), print_error(ERROR), 1);
	if (!thread_create(philo_thread, philos))
		return (cleanup(), print_error(ERROR), 1);
	monitor(philos);
	if (!thread_join(philo_thread, philos))
		return (cleanup(), print_error(ERROR), 1);
	cleanup();
	return (0);
}
