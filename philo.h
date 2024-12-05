#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    int times_eaten;
    long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data *data;
} t_philosopher;

typedef struct s_data {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_each_philosopher_must_eat;
    int all_alive;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philosopher *philosophers;
}   t_data;