

#include "philo.h"

void init_philosopher(t_data *data)
{
    data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
    int i;

    i = 0;
    while(i < data->num_philosophers)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].times_eaten = 0;
        data->philosophers[i].last_meal_time = data->start_time;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data-> num_philosophers];
        data->philosophers[i].data = data;
        i++;
    }

}

void init_data(t_data *data, int argc, char **argv)
{
    data->num_philosophers = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    if(argc == 6)
        data->num_times_each_philosopher_must_eat = atoi(argv[5]);
    else
        data->num_times_each_philosopher_must_eat = -1;
    data->all_alive = 1;
    data->start_time = get_time_in_ms();
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers)
    int i;
    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
}

void start_simulation(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i])
        i++;
    }

    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_join(data->num_philosophers[i].thread, NULL);
        i++;
    }

}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosohper *)arg;
    while(philo->data->all_alive)
    {
        print_status(philo, "is thinking");

        pthread_mutex_lock(philo->left_fork);
        print_status(philo,  "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");

        print_status(philo, "is eating");
        philo->last_meal_time = get_time_in_ms();
        usleep(philo->data->time_to_eat * 1000);
        philo->times_eaten++;

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
    }
    return NULL;
}

void *monitor_death(void *arg)
{
    t_data *data = (t_data *)arg;
    
    while (data->all_alive)
    {
        int i = 0;
        while (i < data->num_philosophers)
        {
            if(get_time_in_ms() - data->philosophers[i].last_meal_time > data->time_to_die)
            {
                print_status(&data->philosophers[i], "died");
                data->all_alive = 0;
                break;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}

long get_time_in_ms() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void print_status(t_philosopher *philo, char *status) {
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}


void destroy_mutexes(t_data *data)
{
    int i = 0;
    while (i < data->num_philosophers)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
}


int main (int argc, char **argv)
{
    if(argc < 5 || argc > 6)
    {
        printf("Usage: &s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return (1);
    }

    t_data data;

    init_data (&data, argc, argv);
    init_philosophers(&data);

    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor_death, &data);

    start_simulation(&data);

    pthread_mutexes(&data);
    free(data.forks);
    free(data.philosophers);


    return (0);
}