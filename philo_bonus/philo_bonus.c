/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:35:16 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/26 00:34:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring(void *args)
{
	t_philo *philos = (t_philo *)args;
	long long	current;
	while (1)
	{
		sem_wait(philos->shared->rip);
		current  = get_time_ms();
		if (current - philos->last_meal >= philos->shared->t_die)
		{
			print_status(philos, DEAD_NOTIF, RED);
			sem_post(philos->shared->stop);
			break;
		}
		sem_post(philos->shared->rip);
		if (philos->shared->meals_num != -1)
		{
		sem_wait(philos->shared->rip);
		if (philos->meals_eaten >= philos->shared->meals_num)
		{
			sem_post(philos->shared->stop);
			break;
		}
		sem_post(philos->shared->rip);
		}
		ft_usleep(1000);
	}
	return (NULL);
}


void	philo_routine(t_philo *philos)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitoring, philos);
	pthread_detach(monitor);
	while (1)
	{
		sem_wait(philos->shared->forks);
		print_status(philos, FORK_NOTIF, GREEN);
		sem_wait(philos->shared->forks);
		print_status(philos, FORK_NOTIF, GREEN);
		print_status(philos, EAT_NOTIF, YELLOW);
		ft_usleep(philos->shared->t_eat);
		sem_wait(philos->shared->rip);
		philos->meals_eaten++;
		philos->last_meal = get_elapsed_time(philos->shared->start);
		sem_post(philos->shared->rip);
		sem_post(philos->shared->forks);
		sem_post(philos->shared->forks);
		print_status(philos, SLEEP_NOTIF, CYAN);
		ft_usleep(philos->shared->t_sleep);
		print_status(philos, THINK_NOTIF, MAGENTA);
	}
}



//=========================================

int	main(int c, char **v)
{
	t_philo		*philos;
	t_shared	data;

	ft_memset(&data, 0, sizeof(t_shared));
	if (!check_args(c, &data))
		return (print_error(ARG_ERROR_NUM), 1);
	if (!valid_args(v, &data))
		return (print_error(ARG_ERROR_ARG), 1);
	philos = malloc(sizeof(t_philo) * data.philo_num);
		if (!philos)
			return(print_error(ERROR), 1);
	int i = 0;
	while (i < data.philo_num)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].shared = &data;
		i++;
	}
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/rip");
	sem_unlink("/stop");
	data.forks = sem_open("/forks", O_CREAT, 0644, data.philo_num);
	data.print = sem_open("/print", O_CREAT, 0644, 1);
	data.rip = sem_open("/rip", O_CREAT, 0644, 1);
	data.stop = sem_open("/stop", O_CREAT, 0644, 1);
	sem_wait(data.stop);
	i = 0;
	data.start = get_time_ms();
	while (i < data.philo_num)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philo_routine(&philos[i]);
			exit(0);
		}
		i++;
		usleep(1000);
	}
	sem_wait(data.stop);
	i = 0;
	while (i < data.philo_num)
	{
		kill(philos[i].philo_id, SIGKILL);
		i++;
	}
	while(waitpid(-1, NULL, 0) > 0)
		;

}
