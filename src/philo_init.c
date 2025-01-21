/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:15:53 by mcentell          #+#    #+#             */
/*   Updated: 2025/01/21 19:57:07 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_mutexes_and_flags(t_philosopher *philosopher,
		t_simulation *simulation)
{
	philosopher->write_lock = &simulation->write_lock;
	philosopher->dead_lock = &simulation->dead_lock;
	philosopher->meal_lock = &simulation->meal_lock;
	philosopher->is_dead = &simulation->dead_flag;
}

void	initialize_philosopher_times(t_philosopher *philosopher, char **argv)
{
	initialize_philosopher_input(philosopher, argv);
	philosopher->start_time = get_current_time();
	philosopher->last_meal = get_current_time();
}

void	initialize_philosopher_state(t_philosopher *philosopher, int id)
{
	philosopher->id = id;
	philosopher->is_eating = 0;
	philosopher->meals_eaten = 0;
}

int	validate_argument_content(char *argument)
{
	while (*argument)
	{
		if (*argument < '0' || *argument > '9')
			return (1);
		argument++;
	}
	return (0);
}

int	validate_arguments(char **arguments)
{
	if (ft_atoi(arguments[1]) > MAX_PHILOSOPHERS || ft_atoi(arguments[1]) <= 0
		|| validate_argument_content(arguments[1]) == 1)
		return (write(2, "Error: Invalid number of philosophers\n", 37), 1);
	if (ft_atoi(arguments[2]) <= 0
		|| validate_argument_content(arguments[2]) == 1)
		return (write(2, "Error: Invalid time to die\n", 27), 1);
	if (ft_atoi(arguments[3]) <= 0
		|| validate_argument_content(arguments[3]) == 1)
		return (write(2, "Error: Invalid time to eat\n", 27), 1);
	if (ft_atoi(arguments[4]) <= 0
		|| validate_argument_content(arguments[4]) == 1)
		return (write(2, "Error: Invalid time to sleep\n", 29), 1);
	if (arguments[5] && (ft_atoi(arguments[5]) < 0
			|| validate_argument_content(arguments[5]) == 1))
		return (write(2, "Error: Invalid number of meals required\n", 40), 1);
	return (0);
}
