#include "philo_bonus.h"

void    *monitoring(void *args)
{
    t_philo     *philos;
    t_shared    *data;
    long long   current;

    philos = (t_philo *)args;
    data = philos->shared;
    while (!philos->stop)
    {
        current = get_elapsed_time(data->start);
        if (current - philos->last_meal >= data->t_die)
        {
            philos->stop = 1;
            print_status(philos, DEAD_NOTIF, RED);
            sem_post(data->rip);
            break;
        }
        usleep(100);
    }
    return (NULL);
}


void manage_process(t_shared *data, t_philo *philos)
{
    int i;

    i = 0;
    data->start = get_time_ms();
    while (i < data->philo_num)
    {
        philos[i].pid = fork();
        if (philos[i].pid < 0)
            return ;
        philos[i].last_meal = data->start;
        if (philos[i].pid == 0)
        {
            pthread_create(&philos[i].thread, NULL, monitoring, &philos[i]);
            philo_routine(&philos[i]);
            pthread_join(philos[i].thread, NULL);
            exit(0);
        }
            usleep(100);
            i++;
        }
}
