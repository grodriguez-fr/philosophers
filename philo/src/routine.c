/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:48:31 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/15 13:36:46 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	lock_fork(t_env *env, int id_fork)
{
	while (1)
	{
		pthread_mutex_lock(&env->forks[id_fork]);
		if (env->fork_values[id_fork])
		{
			env->fork_values[id_fork] = 0;
			return ;
		}
	}
}

void	lock_forks(t_env *env, t_philo *philo)
{
	if (philo->left_fork_id > philo->right_fork_id)
	{
		lock_fork(env, philo->left_fork_id);
		print_log(env, philo, "has taken a fork");
		lock_fork(env, philo->right_fork_id);
		print_log(env, philo, "has taken a fork");
	}
	else
	{
		lock_fork(env, philo->right_fork_id);
		print_log(env, philo, "has taken a fork");
		lock_fork(env, philo->left_fork_id);
		print_log(env, philo, "has taken a fork");
	}
}

void	philo_eat(t_env *env, t_philo *philo)
{
	lock_forks(env, philo);
	print_log(env, philo, "is eating");
	checked_sleep(env->time_eat, env);
	pthread_mutex_lock(philo->meal);
	philo->times_ate++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal);
	env->fork_values[philo->left_fork_id] = 1;
	pthread_mutex_unlock(&env->forks[philo->left_fork_id]);
	env->fork_values[philo->right_fork_id] = 1;
	pthread_mutex_unlock(&env->forks[philo->right_fork_id]);
}

void	one_fork_routine(t_env *env, t_philo *philo)
{
	print_log(env, philo, "has taken a fork");
	checked_sleep(env->time_die * 2, env);
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
		print_log(env, philo, "is sleeping");
		checked_sleep(env->time_sleep, env);
		print_log(env, philo, "is thinking");
		checked_sleep(500, env);
	}
	return (NULL);
}
