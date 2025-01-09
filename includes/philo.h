#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_philosopher
{
    pthread_t       thread;
    int             id;
    int             is_eating;
    int             meals_eaten;
    size_t          last_meal;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    size_t          start_time;
    int             total_philosophers;
    int             required_meals;
    int             *is_dead;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
}                   t_philosopher;

typedef struct s_simulation
{
    int             dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
    t_philosopher   *philosophers;
}                   t_simulation;

// Main functions
int     validate_argument_content(char *argument);
int     validate_arguments(char **arguments);
void    destroy_all(char *message, t_simulation *simulation, pthread_mutex_t *forks);

// Initialization
void    initialize_simulation(t_simulation *simulation, t_philosopher *philosophers);
void    initialize_and_assign_forks(t_philosopher *philosophers, pthread_mutex_t *forks, int num_philosophers);
void    setup_philosophers(t_philosopher *philosophers, t_simulation *simulation, pthread_mutex_t *forks, char **argv);
void    initialize_philosopher_input(t_philosopher *philosopher, char **argv);
void    initialize_philosopher_state(t_philosopher *philosopher, int id);
void    initialize_philosopher_times(t_philosopher *philosopher, char **argv);
void    assign_mutexes_and_flags(t_philosopher *philosopher, t_simulation *simulation);

// Threads
int     create_threads(t_simulation *simulation, pthread_mutex_t *forks);
void    *monitor_simulation(void *pointer);
void    *philosopher_routine(void *pointer);

// Actions
void    philosopher_eat(t_philosopher *philosopher);
void    philosopher_sleep(t_philosopher *philosopher);
void    philosopher_think(t_philosopher *philosopher);

// Monitor utils
int     check_dead_status(t_philosopher *philosopher);
int     check_if_all_philosophers_ate(t_philosopher *philosophers);
int     check_philosophers_status(t_philosopher *philosophers);
int     is_philosopher_dead(t_philosopher *philosopher, size_t time_to_die);

// Utils
int     ft_atoi(char *str);
int     ft_usleep(size_t microseconds);
int     ft_strlen(char *str);
void    print_status_message(char *message, t_philosopher *philosopher, int id);
size_t  get_current_time(void);

#endif