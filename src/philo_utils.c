#include "philo.h"

void	destroy_all(char *str, t_simulation *simulation, pthread_mutex_t *forks)
{
    int	i;

    i = 0;
    if (str)
    {
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
    }
    pthread_mutex_destroy(&simulation->write_lock);
    pthread_mutex_destroy(&simulation->meal_lock);
    pthread_mutex_destroy(&simulation->dead_lock);
    while (i < simulation->philosophers[0].total_philosophers)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}

int	ft_usleep(size_t milliseconds)
{
    size_t	start;

    start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(500);
    return (0);
}

size_t	get_current_time(void)
{
    struct timeval	time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}