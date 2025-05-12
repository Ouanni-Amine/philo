/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:59:18 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/12 15:50:44 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdatomic.h>

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

typedef struct s_shared
{
	long		philo_num;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		meals_num;
	long long	start;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*rip;
}	t_shared;

typedef struct s_philo
{
	atomic_int				is_eating;
	pid_t					pid;
	long					philo_id;
	atomic_long				meals_eaten;
	atomic_llong			last_meal;
	atomic_int				stop;
	pthread_t				thread;
	t_shared				*shared;
}	t_philo;

int			init(t_shared *data, t_philo **philos);
long long	get_time_ms(void);
long long	get_elapsed_time(long long start);
void		*ft_memset(void *b, int c, size_t len);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
long		ft_long_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
void		cleanup(t_philo *philos, t_shared *data);
void		ft_usleep(long long time_ms);
void		print_status(t_philo *philos, char *message, char *color);
void		print_error(char *msg);
void		philo_routine(t_philo *philos);
int			check_args(int c, t_shared *data);
int			valid_args(char **v, t_shared *data);
int			manage_process(t_shared *data, t_philo *philos);

#endif
