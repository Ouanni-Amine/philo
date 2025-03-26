#include "philo_bonus.h"

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
    sem_post(philos->shared->print);
}

void	print_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
}