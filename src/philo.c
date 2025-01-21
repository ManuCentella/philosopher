/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:50:48 by mcentell          #+#    #+#             */
/*   Updated: 2025/01/21 19:53:49 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;
	t_philosopher	philosophers[MAX_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (argc != 5 && argc != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	if (validate_arguments(argv) == 1)
		return (1);
	initialize_simulation_components(&simulation, philosophers, forks, argv);
	create_and_join_threads(philosophers, argv);
	return (0);
}
