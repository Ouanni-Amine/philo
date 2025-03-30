#include "philo_bonus.h"

void    philo_routine(t_philo *philos)
{
    t_shared    *data;

    data = philos->shared;
    while(!philos->stop)
    {
        if (data->meals_num != -1 && philos->meals_eaten >= data->meals_num)
        {
            philos->stop = 1;
            sem_post(data->rip);
            return ;
        }
        sem_wait(data->forks);
        print_status(philos, FORK_NOTIF, GREEN);
        if (data->philo_num == 1)
        {
            ft_usleep(data->t_die);
            print_status(philos, DEAD_NOTIF, RED);
            sem_post(data->forks);
            sem_post(data->rip);
            return ;
        }
        sem_wait(data->forks);
        print_status(philos, FORK_NOTIF, GREEN);
        philos->last_meal = get_elapsed_time(data->start);
        print_status(philos, EAT_NOTIF, YELLOW);
        philos->meals_eaten++;
        ft_usleep(data->t_eat);
        sem_post(data->forks);
        sem_post(data->forks);
        if (philos->stop)
            break;
        print_status(philos, SLEEP_NOTIF, CYAN);
        ft_usleep(data->t_sleep);
        if (philos->stop)
            break;
        print_status(philos, THINK_NOTIF, MAGENTA);
        ft_usleep(1);
    }
}
