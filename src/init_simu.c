/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:43 by mcentell          #+#    #+#             */
/*   Updated: 2025/01/21 20:17:33 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_simulation_components(t_simulation *simulation,
		t_philosopher *philosophers, pthread_mutex_t *forks, char **argv)
{
	initialize_simulation(simulation, philosophers);
	initialize_and_assign_forks(philosophers, forks, ft_atoi(argv[1]));
	setup_philosophers(philosophers, simulation, argv);
}

void	initialize_simulation(t_simulation *simulation,
		t_philosopher *philosophers)
{
	simulation->dead_flag = 0;
	simulation->philosophers = philosophers;
	pthread_mutex_init(&simulation->write_lock, NULL);
	pthread_mutex_init(&simulation->dead_lock, NULL);
	pthread_mutex_init(&simulation->meal_lock, NULL);
}

void	initialize_and_assign_forks(t_philosopher *philosophers,
		pthread_mutex_t *forks, int num_philosophers)
{
	int	i;

	i = 0;
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

void	setup_philosophers(t_philosopher *philosophers,
		t_simulation *simulation, char **argv)
{
	int				i;
	int				num_philosophers;
	t_philosopher	*philo;

	num_philosophers = ft_atoi(argv[1]);
	i = 0;
	while (i < num_philosophers)
	{
		philo = &philosophers[i];
		initialize_philosopher_state(philo, i + 1);
		initialize_philosopher_times(philo, argv);
		assign_mutexes_and_flags(philo, simulation);
		i++;
	}
}
