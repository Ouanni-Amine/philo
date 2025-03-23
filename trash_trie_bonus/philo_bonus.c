/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:32:44 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/22 23:33:53 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
}

int	should_stop(t_process *philo)
{
	sem_wait(philo->rip);
	if (philo->die)
	{
		sem_post(philo->rip);
		return (1);
	}
	else if (philo->full)
	{
		sem_post(philo->rip);
		return (2);
	}
	sem_post(philo->rip);
	return (0);
}

void	print_status(t_info *data, char *message, char *color, int rip)
{
	long long time;

	sem_wait(data->print);
	if (rip  && ft_strcmp(message, "is died"))
	{
		sem_post(data->print);
		return;
	}
	time = get_elapsed_time(data->start);
	printf("%s%lld %ld %s%s\n", color, time, data->id, message, RESET);
	sem_post(data->print);
}

void	ft_usleep(long long time_ms, int rip)
{
	long long	start;

	start = get_time_ms();
	while (!rip && get_elapsed_time(start) < time_ms)
		usleep(50);
}

void	*monitor(void *args)
{
	t_info *data = (t_info *)args;

	while (1)
	{
		int status ;
		if (status = should_stop(data->process))
			{
				if (status)
			}
	}
}

void	philo_routine(t_info *data)//TODO: check the retunr value of ur thread functions!!!
{
	t_process philo;

	ft_memset(&philo, 0, sizeof(t_process));
	philo.last_meal = data->start;
	philo.meals_eaten = 0;
	philo.rip = open("/rip", O_CREAT, 0644, 1);
	if (philo.rip == SEM_FAILED)
		exit(1);
	data->process = &philo;
	pthread_t *monitor;
	pthread_create(&monitor, NULL, monitor, data);
	pthread_detach(monitor);
	while (1)
	{
		if (should_stop(&philo) == 1)
			exit(1);
		else
			exit(0);
		sem_wait(data->seat);
		sem_wait(data->forks);
		print_status(data, FORK_NOTIF, GREEN, should_stop(&philo));
		if (data->philo_num == 1)
		{
			ft_usleep(data->t_die, should_stop(&philo));
			print_status(data, DEAD_NOTIF, RED, should_stop(&philo));
			sem_post(data->seat);
			sem_post(data->forks);
			exit(1);
		}
		sem_wait(data->forks);
		print_status(data, FORK_NOTIF, GREEN, should_stop(&philo));
		int status;
		if (status = should_stop(&philo))
		{
			sem_post(data->seat);
			sem_post(data->forks);
			sem_post(data->forks);
		if (status == 1)
			exit(1);
		else
			exit(2);
		}
		sem_wait(data->process->rip);
		data->process->last_meal = get_elapsed_time(data->start);
		data->process->meals_eaten++;
		sem_post(data->process->rip);
		print_status(data, EAT_NOTIF, YELLOW, should_stop(&philo));
		ft_usleep(data->t_eat, should_stop(&philo));
		sem_post(data->seat);
		sem_post(data->forks);
		sem_post(data->forks);
		print_status(data, SLEEP_NOTIF, CYAN, should_stop(&philo));
		ft_usleep(data->t_sleep, should_stop(&philo));
		print_status(data, THINK_NOTIF, MAGENTA, should_stop(&philo));
}
}

int	main(int c, char **v)
{
	t_info	data;
	int 	i;

	i = 0;
	ft_memset(&data, 0, sizeof(t_info));
	if (!check_args(c, &data))
		return (print_error(ARG_ERROR_NUM), 1);
	if (!valid_args(v, &data))
		return (print_error(ARG_ERROR_ARG), 1);
	data.pid = malloc(sizeof(pid_t) * data.philo_num);//NOTE ; u have the right to use exit so use old ft_malloc
	if (!data.pid)
		return (print_error(ERROR), 1);
	data.forks = sem_open("/forks", O_CREAT, 0644, data.philo_num);
	data.print = sem_open("/print", O_CREAT, 0644, 1);
	data.seat = sem_open("/seat", O_CREAT, 0644, data.philo_num - 1);
	if (data.forks == SEM_FAILED || data.print == SEM_FAILED || data.seat == SEM_FAILED)
		return (cleanup(&data), print_error(ERROR), 1);
	data.start = get_time_ms();
	while (i < data.philo_num)
	{
		data.id = i + 1;
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (cleanup(&data), print_error(ERROR), 1);//TODO: check return value of sem_close!!
		if (data.pid[i] == 0)
			philo_routine(&data);
		i++;
	}
	int status;
	int i = 0;
	while (waitpid(-1,&status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			while (i < data.philo_num)
			{
				kill(data.pid[i], SIGKILL);
				i++;
			}
			while (waitpid(-1, NULL, 0) > 0)
			;
			break;
		}
	}
	cleanup(&data);
}
