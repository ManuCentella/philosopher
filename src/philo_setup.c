#include "philo.h"

void initialize_philosopher_input(t_philosopher *philosopher, char **argv)
{
    philosopher->time_to_die = ft_atoi(argv[2]);
    philosopher->time_to_eat = ft_atoi(argv[3]);
    philosopher->time_to_sleep = ft_atoi(argv[4]);
    philosopher->total_philosophers = ft_atoi(argv[1]);
    if (argv[5])
        philosopher->required_meals = ft_atoi(argv[5]);
    else
        philosopher->required_meals = -1;
}


void initialize_simulation(t_simulation *simulation, t_philosopher *philosophers)
{
    simulation->dead_flag = 0;
    simulation->philosophers = philosophers;
    pthread_mutex_init(&simulation->write_lock, NULL);
    pthread_mutex_init(&simulation->dead_lock, NULL);
    pthread_mutex_init(&simulation->meal_lock, NULL);
}
