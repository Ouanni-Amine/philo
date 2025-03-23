/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:35:16 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/23 21:10:10 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

long	ft_long_atoi(const char *str)
{
	int			sign;
	long		res;
	int			i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

long long	get_time_ms(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

long long	get_elapsed_time(long long start)
{
	long long	current;

	current = get_time_ms();
	return (current - start);
}

//=================parsing================
int	check_args(int c, t_shared *data)
{
	if (c < 5 || c > 6)
		return (0);
	if (c == 5)
		data->meals_num = -1;
	return (1);
}

int	check_single(char *v)
{
	int	i;

	i = 0;
	if (v[i] == '+')
		i++;
	while (v[i])
	{
		if (!ft_isdigit(v[i]))
			return (0);
		i++;
	}
	return (1);
}

int	fill_args_p2(long res, t_shared *data, int i)
{
	if (i == 1)
	{
		if (res == 0 || res > 200)
			return (0);
		data->philo_num = (int)res;
	}
	else if ((i >= 2 && i <= 4) && res < 60)
		return (0);
	else if (i == 2)
		data->t_die = (int)res;
	else if (i == 3)
		data->t_eat = (int)res;
	else if (i == 4)
		data->t_sleep = (int)res;
	else
	{
		if (res == 0)
			return (0);
		data->meals_num = (int)res;
	}
	return (1);
}

int	fill_args(int i, char *v, t_shared *data)
{
	int		j;
	long	res;

	j = 0;
	if (v[j] == '+')
		j++;
	while (v[j] == '0')
		j++;
	if (ft_strlen(v + j) > 10)
		return (0);
	res = ft_long_atoi(v);
	if (res > 2147483647 || res < 0)
		return (0);
	if (!fill_args_p2(res, data, i))
		return (0);
	return (1);
}

int	valid_args(char **v, t_shared *data)
{
	int	i;

	i = 1;
	while (v[i])
	{
		if (v[i][0] == '\0')
			return (0);
		if (!check_single(v[i]))
			return (0);
		if (!fill_args(i, v[i], data))
			return (0);
		i++;
	}
	return (1);
}
//========================================

void	ft_usleep(long long time_ms)
{
	long long	start;

	start = get_time_ms();
	while (get_elapsed_time(start) < time_ms)
		usleep(50);
}

void	print_status(t_philo *philos, char *message, char *color)
{
	long long time;

	sem_wait(philos->shared->print);
	time = get_elapsed_time(philos->shared->start);
	printf("%s%lld %ld %s%s\n", color, time, philos->philo_id, message, RESET);
	if (strcmp(message , "is died"))
		sem_post(philos->shared->print);
}

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
void	print_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
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
