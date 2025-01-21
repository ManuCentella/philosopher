/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:35:07 by mcentell          #+#    #+#             */
/*   Updated: 2025/01/21 20:01:49 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status_message(char *message, t_philosopher *philosopher,
		int philosopher_id)
{
	size_t	current_time;

	pthread_mutex_lock(philosopher->write_lock);
	current_time = get_current_time() - philosopher->start_time;
	if (!*philosopher->is_dead)
		printf("%zu %d %s\n", current_time, philosopher_id, message);
	pthread_mutex_unlock(philosopher->write_lock);
}

int	is_philosopher_dead(t_philosopher *philosopher, size_t time_to_die)
{
	pthread_mutex_lock(philosopher->meal_lock);
	if (get_current_time() - philosopher->last_meal >= time_to_die
		&& philosopher->is_eating == 0)
		return (pthread_mutex_unlock(philosopher->meal_lock), 1);
	pthread_mutex_unlock(philosopher->meal_lock);
	return (0);
}

int	check_philosophers_status(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers[0].total_philosophers)
	{
		if (is_philosopher_dead(&philosophers[i], philosophers[i].time_to_die))
		{
			print_status_message("died", &philosophers[i], philosophers[i].id);
			pthread_mutex_lock(philosophers[0].dead_lock);
			*philosophers->is_dead = 1;
			pthread_mutex_unlock(philosophers[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_philosophers_ate(t_philosopher *philosophers)
{
	int	i;
	int	finished_eating_count;

	i = 0;
	finished_eating_count = 0;
	if (philosophers[0].required_meals == -1)
		return (0);
	while (i < philosophers[0].total_philosophers)
	{
		pthread_mutex_lock(philosophers[i].meal_lock);
		if (philosophers[i].meals_eaten >= philosophers[i].required_meals)
			finished_eating_count++;
		pthread_mutex_unlock(philosophers[i].meal_lock);
		i++;
	}
	if (finished_eating_count == philosophers[0].total_philosophers)
	{
		pthread_mutex_lock(philosophers[0].dead_lock);
		*philosophers->is_dead = 1;
		pthread_mutex_unlock(philosophers[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_simulation(void *pointer)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)pointer;
	while (1)
		if (check_philosophers_status(philosophers) == 1
			|| check_if_all_philosophers_ate(philosophers) == 1)
			break ;
	return (pointer);
}
