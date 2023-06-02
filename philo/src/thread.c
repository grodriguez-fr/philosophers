/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:41:47 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/02 15:41:17 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	check_death_and_eats(t_env *env)
{
	int	i;

	while (!env->anyone_died && !env->all_finished_eat)
	{
		i = 0;
		pthread_mutex_lock(env->meal);
		while (i < env->nb_philo)
		{
			if (env->philosophers[i++].last_meal + env->time_die < get_time())
			{
				print_log(env, &env->philosophers[i - 1], "died", 0);
				pthread_mutex_lock(env->end_simulation);
				env->anyone_died++;
				pthread_mutex_unlock(env->end_simulation);
			}
		}
		i = 0;
		while (i < env->nb_philo && env->philosophers[i].times_ate \
				>= env->nb_eat && env->nb_eat != -1)
			i++;
		pthread_mutex_unlock(env->meal);
		pthread_mutex_lock(env->end_simulation);
		if (i == env->nb_philo)
			env->all_finished_eat = 1;
		pthread_mutex_unlock(env->end_simulation);
		usleep(100);
	}
}

int	start_thread(t_env *env)
{
	int		i;
	t_philo	*p;

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
