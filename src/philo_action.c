#include "philo.h"

void philosopher_think(t_philosopher *philosopher)
{
    print_status_message("is thinking", philosopher, philosopher->id);
}

void philosopher_sleep(t_philosopher *philosopher)
{
    print_status_message("is sleeping", philosopher, philosopher->id);
    ft_usleep(philosopher->time_to_sleep);
}

void philosopher_eat(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->right_fork);
    print_status_message("has taken a fork", philosopher, philosopher->id);
    if (philosopher->total_philosophers == 1)
    {
        ft_usleep(philosopher->time_to_die);
        pthread_mutex_unlock(philosopher->right_fork);
        return ;
    }
    pthread_mutex_lock(philosopher->left_fork);
    print_status_message("has taken a fork", philosopher, philosopher->id);
    philosopher->is_eating = 1;
    print_status_message("is eating", philosopher, philosopher->id);
    pthread_mutex_lock(philosopher->meal_lock);
    philosopher->last_meal = get_current_time();
    philosopher->meals_eaten++;
    pthread_mutex_unlock(philosopher->meal_lock);
    ft_usleep(philosopher->time_to_eat);
    philosopher->is_eating = 0;
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
}