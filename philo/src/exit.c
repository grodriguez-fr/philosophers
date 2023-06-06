/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:36 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/06 14:19:29 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	exit_philo(t_env *env, int exit_code)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_join(env->philosophers[i].thread_id, NULL);
		pthread_mutex_destroy(env->philosophers[i].meal);
        free(env->philosophers[i++].meal);
	}
	i = 0;
	while (i < env->nb_philo)
		pthread_mutex_destroy(&env->forks[i++]);
	if (env->writing)
		pthread_mutex_destroy(env->writing);
	if (env->end_simulation)
		pthread_mutex_destroy(env->writing);
	if (env->end_simulation)
		free(env->end_simulation);
	if (env->forks)
		free(env->forks);
	if (env->philosophers)
		free(env->philosophers);
	if (env->writing)
		free(env->writing);
	if (env->fork_values)
		free(env->fork_values);
	exit(exit_code);
}
