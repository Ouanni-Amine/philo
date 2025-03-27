#include "philo_bonus.h"

int manage_process(t_shared *data, t_philo *philos)
{
    int i;

    i = 0;
    while (i < data->philo_num)
    {
        philos[i].pid = fork();
        if (philos[i].pid < 0)
            return(0);
        data->start = get_time_ms();
        philos[i].last_meal = data->start;
        if (philos[i].pid == 0)
        {
            philo_routine(philos[i]);
            exit(0);
        }
        i++;
        usleep(100);
    }
    return (1);
}
