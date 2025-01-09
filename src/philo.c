#include "philo.h"

int validate_argument_content(char *argument)
{
    int index = 0;
    while (argument[index] != '\0')
    {
        if (argument[index] < '0' || argument[index] > '9')
            return (1);
        index++;
    }
    return (0);
}

int validate_arguments(char **arguments)
{
    if (ft_atoi(arguments[1]) > MAX_PHILOSOPHERS || ft_atoi(arguments[1]) <= 0 || validate_argument_content(arguments[1]) == 1)
        return (write(2, "Invalid philosophers number\n", 29), 1);
    if (ft_atoi(arguments[2]) <= 0 || validate_argument_content(arguments[2]) == 1)
        return (write(2, "Invalid time to die\n", 21), 1);
    if (ft_atoi(arguments[3]) <= 0 || validate_argument_content(arguments[3]) == 1)
        return (write(2, "Invalid time to eat\n", 21), 1);
    if (ft_atoi(arguments[4]) <= 0 || validate_argument_content(arguments[4]) == 1)
        return (write(2, "Invalid time to sleep\n", 23), 1);
    if (arguments[5] && (ft_atoi(arguments[5]) < 0 || validate_argument_content(arguments[5]) == 1))
        return (write(2, "Invalid number of times each philosopher must eat\n", 51), 1);
    return (0);
}

#include "philo.h"

void initialize_simulation_components(t_simulation *simulation, t_philosopher *philosophers, pthread_mutex_t *forks, char **argv)
{
    initialize_simulation(simulation, philosophers);
    initialize_and_assign_forks(philosophers, forks, ft_atoi(argv[1]));
    setup_philosophers(philosophers, simulation, forks, argv);
}

void create_and_join_threads(t_philosopher *philosophers, char **argv)
{
    pthread_t monitor_thread;
    int i = 0;

    pthread_create(&monitor_thread, NULL, monitor_simulation, philosophers);

    while (i < ft_atoi(argv[1]))
    {
        pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
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

int main(int argc, char **argv)
{
    t_simulation simulation;
    t_philosopher philosophers[MAX_PHILOSOPHERS];
    pthread_mutex_t forks[MAX_PHILOSOPHERS];

    if (argc != 5 && argc != 6)
        return (write(2, "Wrong argument count\n", 22), 1);
    if (validate_arguments(argv) == 1)
        return (1);

    initialize_simulation_components(&simulation, philosophers, forks, argv);
    create_and_join_threads(philosophers, argv);

    return (0);
}
