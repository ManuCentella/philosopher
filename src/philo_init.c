/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:15:53 by mcentell          #+#    #+#             */
/*   Updated: 2025/01/09 16:45:23 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void setup_philosophers(t_philosopher *philosophers, t_simulation *simulation, pthread_mutex_t *forks, char **argv)
{
    int i = 0;
    int num_philosophers = ft_atoi(argv[1]);

    initialize_and_assign_forks(philosophers, forks, num_philosophers);

    while (i < num_philosophers)
    {
        t_philosopher *philo = &philosophers[i];
        initialize_philosopher_state(philo, i + 1);
        initialize_philosopher_times(philo, argv);
        assign_mutexes_and_flags(philo, simulation);

        i++;
    }
}

void initialize_and_assign_forks(t_philosopher *philosophers, pthread_mutex_t *forks, int num_philosophers)
{
    int i = 0;
    while (i < num_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);

        philosophers[i].left_fork = &forks[i];
        if (i == 0)
        {
            philosophers[i].right_fork = &forks[num_philosophers - 1];
        }
        else
        {
            philosophers[i].right_fork = &forks[i - 1];
        }

        i++;
    }
}

void assign_mutexes_and_flags(t_philosopher *philosopher, t_simulation *simulation)
{
    philosopher->write_lock = &simulation->write_lock;
    philosopher->dead_lock = &simulation->dead_lock;
    philosopher->meal_lock = &simulation->meal_lock;
    philosopher->is_dead = &simulation->dead_flag;
}
void initialize_philosopher_times(t_philosopher *philosopher, char **argv)
{
    initialize_philosopher_input(philosopher, argv);
    philosopher->start_time = get_current_time();
    philosopher->last_meal = get_current_time();
}
void initialize_philosopher_state(t_philosopher *philosopher, int id)
{
    philosopher->id = id;
    philosopher->is_eating = 0;
    philosopher->meals_eaten = 0;
}