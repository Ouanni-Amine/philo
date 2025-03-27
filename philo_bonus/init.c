#include "philo_bonus.h"

int init_sems(t_shared *data)
{
    sem_unlink("/froks");
    sem_unlink("/print");
    sem_unlink("/rip");
    data->froks = sem_open("/forks", O_CREAT, 0644, data->philo_num);
    data->print = sem_open("/print", O_CREAT, 0644, 1);
    data->print = sem_open("/rip", O_CREAT, 0644, 0);
    if (data->forks == SEM_FAILED || data->print == SEM_FAILED
        || data->rip == SEM_FAILED)
        return (0);
    return (1);
}

int init(t_shared *data, t_philo **philos)
{
    int i;

    i = 0;
    philos = malloc(sizeof(t_philo) * data.philo_num);
    if (!philos)
        return (0);
    while (i < data->philo_num)
    {
        philos[i].philo_id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].shared = data;
        i++;
    }
    if (!init_sems(data))
        return (0);
    return(1);
}
