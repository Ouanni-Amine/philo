/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:20:56 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/22 23:37:51 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>//NOTE : for thread if not used remove it
#include <semaphore.h>//NOTE: for semaphores
#include <signal.h>//NOTE: for kill
#include <sys/time.h>

# define RED "\033[31m"
# define GREEN   "\033[32m"
# define RESET "\033[0m"
# define YELLOW  "\033[33m"
# define CYAN    "\033[36m"
# define MAGENTA "\033[35m"

# define ARG_ERROR_NUM "Warning: Invalide number of arguments found"
# define ARG_ERROR_ARG "Warning: Invalide argument found"
# define ERROR "Warning: Error happend"
# define FORK_NOTIF "has taken a fork"
# define DEAD_NOTIF "is died"
# define EAT_NOTIF "is eating"
# define SLEEP_NOTIF "is sleeping"
# define THINK_NOTIF "is thinking"

typedef struct s_info
{
	long	philo_num;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	meals_num;
	long	start;
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*seat;
	int 	id;
	t_process	*process;
}	t_info;

typedef struct s_process
{
	sem_t	*rip;
	int		die;
	int		full;
	long	last_meal;
	long	meals_eaten;
}	t_process;


void		*ft_memset(void *b, int c, size_t len);
int			valid_args(char **v, t_info *data);
int			check_args(int c, t_info *data);
long		ft_long_atoi(const char *str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		print_error(char *msg);
void		cleanup(t_info *data);
long long	get_time_ms(void);
long long	get_elapsed_time(long long start);
void		ft_usleep(long long time_ms, int rip);
#endif
