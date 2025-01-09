#include "philo.h"

int check_dead_status(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->dead_lock);
    if (*philosopher->is_dead == 1)
    {
        pthread_mutex_unlock(philosopher->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philosopher->dead_lock);
    return (0);
}

void *philosopher_routine(void *pointer)
{
    t_philosopher *philosopher;

    philosopher = (t_philosopher *)pointer;
    if (philosopher->id % 2 == 0)
        ft_usleep(1);
    while (!check_dead_status(philosopher))
    {
        philosopher_eat(philosopher);
        philosopher_sleep(philosopher);
        philosopher_think(philosopher);
    }
    return (pointer);
}

int create_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
    pthread_t monitor_thread;
    int i;

    if (pthread_create(&monitor_thread, NULL, &monitor_simulation, simulation->philosophers) != 0)
        destroy_all("Thread creation error", simulation, forks);
    i = 0;
    while (i < simulation->philosophers[0].total_philosophers)
    {
        if (pthread_create(&simulation->philosophers[i].thread, NULL, &philosopher_routine,
                &simulation->philosophers[i]) != 0)
            destroy_all("Thread creation error", simulation, forks);
        i++;
    }
    i = 0;
    if (pthread_join(monitor_thread, NULL) != 0)
        destroy_all("Thread join error", simulation, forks);
    while (i < simulation->philosophers[0].total_philosophers)
    {
        if (pthread_join(simulation->philosophers[i].thread, NULL) != 0)
            destroy_all("Thread join error", simulation, forks);
        i++;
    }
    return (0);
}