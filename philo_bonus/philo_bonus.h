/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:35:51 by aouanni           #+#    #+#             */
/*   Updated: 2025/03/23 19:48:17 by aouanni          ###   ########.fr       */
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
#endif

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
	sem_t		*forks;
	sem_t		*print;
	sem_t		*stop;
	sem_t		*rip;
	long		philo_num;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		meals_num;
	long long	start;
}	t_shared;

typedef struct s_philo
{
	t_shared		*shared;
	pid_t			pid;
	long			meals_eaten;
	long			philo_id;
	long long		last_meal;//todo
}	t_philo;
