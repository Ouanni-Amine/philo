#include "philo_bonus.h"

int main(int c , char **v)
{
    t_philo     *philos;
    t_shared    data;

    ft_memset(&data, 0, sizeof(t_shared));
    if (!check_args(c, &data))
        return (print_error(ARG_ERROR_NUM), 1);
    if (!valid_args(c, &data))
        return (print_error(ARG_ERROR_ARG), 1);
    if (!init(&data, &philos))
        return (cleanup(philos, &data), print_error(ERROR), 1);
    if (!manage_process(&data, philos))
        return (cleanup(philos, &data), print_error(ERROR), 1);
}
