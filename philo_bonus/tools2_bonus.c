#include "philo_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
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
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}

void	cleanup(t_philo *philos, t_shared *data)//NOTE: chck the return value of close && unlink
{
	if (philos)
		free(philos);
	if (data->forks != SEM_FAILED)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	if (data->print != SEM_FAILED)
	{
		sem_close(data->print);
		sem_unlink("/print");
	}
	if (data->rip != SEM_FAILED)
	{
		sem_close(data->rip);
		sem_unlink("/seat");
	}
}