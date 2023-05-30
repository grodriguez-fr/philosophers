#include "philosophers.h"

void    philo_eat(t_env *env, t_philo *philo)
{
    pthread_mutex_lock(&env->forks[philo->left_fork_id]);
    print_log(env, philo, "has taken a fork");
    pthread_mutex_lock(&env->forks[philo->right_fork_id]);
    print_log(env, philo, "has taken a fork");
    print_log(env, philo, "is eating");
    checked_sleep(env->time_eat, env);
    pthread_mutex_lock(env->meal);
    philo->times_ate++;
    philo->last_meal = get_time();
    pthread_mutex_unlock(env->meal);
    pthread_mutex_unlock(&env->forks[philo->left_fork_id]);
    pthread_mutex_unlock(&env->forks[philo->right_fork_id]);
}

void    one_fork_routine(t_env *env, t_philo *philo)
{
    print_log(env, philo, "has taken a fork");
    checked_sleep(env->time_die * 2, env);
}

void    *routine(void   *philo_void)
{
    t_philo *philo;
    t_env   *env;

    philo = (t_philo *)philo_void;
    env = philo->env;
    if (env->nb_philo == 1)
        return (one_fork_routine(env, philo), NULL);
    if (philo->id % 2 == 0)
        usleep(15000);
    while (!env->anyone_died)
    {
        philo_eat(env, philo);
        if (env->all_finished_eat)
            return (NULL);
        print_log(env, philo, "is sleeping");
        checked_sleep(env->time_sleep, env);
        print_log(env, philo, "is thinking");
    }
    return (NULL);
}

void    check_death_and_eats(t_env *env)
{
    int i;

    while(!env->anyone_died && !env->all_finished_eat)
    {
        i = 0;
        while (i < env->nb_philo)
        {
            pthread_mutex_lock(env->meal);
            if (env->philosophers[i++].last_meal + env->time_die < get_time())
            {
                print_log(env, &env->philosophers[i - 1], "died");
                env->anyone_died++;
            }
            pthread_mutex_unlock(env->meal);
        }
        i = 0;
        while (i < env->nb_philo && env->philosophers[i].times_ate >= env->nb_eat && env->nb_eat != -1)
            i++;
        if (i == env->nb_philo)
            env->all_finished_eat = 1;
        usleep(100);
    }
}

int start_thread(t_env *env)
{
    int         i;
    t_philo     *p;

    i = 0;
    p = env->philosophers;
    env->time_start = get_time();
    while (i < env->nb_philo)
    {
        if (pthread_create(&p[i].thread_id, NULL, routine, &(p[i])))
            return (0);
        p[i].last_meal = get_time();
        i++;
    }
    check_death_and_eats(env);
    return (0);
}
