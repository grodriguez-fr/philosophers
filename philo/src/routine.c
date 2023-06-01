#include "philosophers.h"

void    lock_forks(t_env *env, t_philo *philo)
{
    if (philo->left_fork_id > philo->right_fork_id)
    {
	    pthread_mutex_lock(&env->forks[philo->left_fork_id]);
	    print_log(env, philo, "has taken a fork");
	    pthread_mutex_lock(&env->forks[philo->right_fork_id]);
	    print_log(env, philo, "has taken a fork");
    }
    else
    {
	    pthread_mutex_lock(&env->forks[philo->right_fork_id]);
	    print_log(env, philo, "has taken a fork");
	    pthread_mutex_lock(&env->forks[philo->left_fork_id]);
	    print_log(env, philo, "has taken a fork");
    }
}
void	philo_eat(t_env *env, t_philo *philo)
{
    lock_forks(env, philo);
	print_log(env, philo, "is eating");
	checked_sleep(env->time_eat, env);
	pthread_mutex_lock(env->meal);
	philo->times_ate++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(env->meal);
	pthread_mutex_unlock(&env->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&env->forks[philo->right_fork_id]);
}

void	one_fork_routine(t_env *env, t_philo *philo)
{
	print_log(env, philo, "has taken a fork");
	checked_sleep(env->time_die * 2, env);
	printf("fin routine\n");
}

void	*routine(void *philo_void)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)philo_void;
	env = philo->env;
	if (env->nb_philo == 1)
		return (one_fork_routine(env, philo), NULL);
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
	    pthread_mutex_lock(env->end_simulation);
        if (env->anyone_died || env->all_finished_eat)
        {
	        pthread_mutex_unlock(env->end_simulation);
            return (NULL);
        }
        pthread_mutex_unlock(env->end_simulation);
		philo_eat(env, philo);
		if (env->all_finished_eat)
			return (NULL);
		print_log(env, philo, "is sleeping");
		checked_sleep(env->time_sleep, env);
		print_log(env, philo, "is thinking");
	}
	return (NULL);
}