/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:35:00 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/12 16:48:10 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN   "\033[32m"
# define RESET "\033[0m"
# define YELLOW  "\033[33m"
# define CYAN    "\033[36m"
# define MAGENTA "\033[35m"

# define ARG_ERROR_NUM "Warning: Invalide number of arguments found"
# define ARG_ERROR_ARG "Warning: Invalide argument found"
# define ERROR "Warning: Error happend"
# define ERROR_MUTEX "Warning: Some mutexes failed to destroy properly"
# define FORK_NOTIF "has taken a fork"
# define DEAD_NOTIF "is died"
# define EAT_NOTIF "is eating"
# define SLEEP_NOTIF "is sleeping"
# define THINK_NOTIF "is thinking"

typedef struct s_shared
{
	int				rip;
	int				full;
	long			philo_num;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			meals_num;
	long long		start;
	pthread_mutex_t	rip_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
}	t_shared;

typedef struct s_philo
{
	int				is_eating;
	long			philo_id;
	long			meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_shared		*shared_data;
}	t_philo;

void		*ft_memset(void *b, int c, size_t len);
int			check_args(int c, t_shared *shared);
int			valid_args(char **v, t_shared *shared);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
long		ft_long_atoi(const char *str);
void		ft_free(void *ptr, int flag);
void		*ft_malloc(size_t n);
int			ft_strcmp(char *s1, char *s2);
long long	get_elapsed_time(long long start);
long long	get_time_ms(void);
int			init(t_shared *data, t_philo **philos, pthread_t **philo_thread);
int			thread_create(pthread_t *philo_thread, t_philo *philos);
int			thread_join(pthread_t *philo_thread, t_philo *philos);
void		*philo_routine(void *args);
int			should_stop(t_philo *philos);
void		print_status(t_philo *philos, char *message, char *color, int rip);
void		ft_usleep(long long time_ms, int rip, t_philo *philos);
void		monitor(t_philo *philos);
void		cleanup(void);
int			mutex_manager(pthread_mutex_t *mutex, int flag);
void		print_error(char *msg);

#endif
