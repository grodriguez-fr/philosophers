#include "philosophers.h"

void    exit_philo(t_env *env, int exit_code)
{
    int i;

    i = 0;
    while (i < env->nb_philo)
        pthread_join(env->philosophers[i++].thread_id, NULL);
    i = 0;
    while (i < env->nb_philo)
        pthread_mutex_destroy(&env->forks[i++]);
    if (env->meal)
        pthread_mutex_destroy(env->meal);
    if (env->writing)
        pthread_mutex_destroy(env->writing);
    if (env->forks)
        free(env->forks);
    if (env->philosophers)
        free(env->philosophers);
    if (env->writing)
        free(env->writing);
    if (env->meal)
        free(env->meal);
    exit(exit_code);
}
