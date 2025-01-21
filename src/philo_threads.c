/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:50:17 by mcentell          #+#    #+#             */
/*   Updated: 2025/01/21 20:04:55 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_status(t_philosopher *philosopher)
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

void	*philosopher_routine(void *pointer)
{
	t_philosopher	*philosopher;

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

int	create_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &monitor_simulation,
			simulation->philosophers) != 0)
		destroy_all("Thread creation error", simulation, forks);
	i = 0;
	while (i < simulation->philosophers[0].total_philosophers)
	{
		if (pthread_create(&simulation->philosophers[i].thread, NULL,
				&philosopher_routine, &simulation->philosophers[i]) != 0)
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

void	create_and_join_threads(t_philosopher *philosophers, char **argv)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	pthread_create(&monitor_thread, NULL, monitor_simulation, philosophers);
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
			&philosophers[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
