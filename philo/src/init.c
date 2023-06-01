/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:48:02 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/01 11:25:42 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	init_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
		pthread_mutex_init(&env->forks[i++], NULL);
	env->writing = malloc(sizeof(pthread_mutex_t));
	if (!env->writing)
		return (0);
	pthread_mutex_init(env->writing, NULL);
	env->meal = malloc(sizeof(pthread_mutex_t));
	if (!env->meal)
		return (0);
	pthread_mutex_init(env->meal, NULL);
	env->end_simulation = malloc(sizeof(pthread_mutex_t));
	if (!env->end_simulation)
		return (0);
	pthread_mutex_init(env->end_simulation, NULL);
	return (1);
}

int	init_philo(t_env *env)
{
	int	i;

	env->forks = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->forks)
		return (0);
	env->philosophers = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->philosophers)
		return (0);
	i = 0;
	while (i < env->nb_philo)
	{
		env->philosophers[i].id = i + 1;
		env->philosophers[i].times_ate = 0;
		env->philosophers[i].left_fork_id = (i + 1) % env->nb_philo;
		env->philosophers[i].right_fork_id = i;
		env->philosophers[i].last_meal = 0;
		env->philosophers[i].env = env;
		i++;
	}
	return (1);
}

int	check_vars(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_vars(int argc, char **argv, t_env *env)
{
	env->philosophers = NULL;
	env->forks = NULL;
	env->nb_philo = 0;
	env->writing = NULL;
	env->meal = NULL;
	env->end_simulation = NULL;
	if (argc != 5 && argc != 6)
		return (ft_putstr_err("Wrong arg number, usage : ./philo [nb] \
		[time_die] [time_eat] [time_sleep]\n"), 0);
	if (!check_vars(argv))
	{
		return (ft_putstr_err("Enter numeric arguments only\n"), 0);
	}
	env->nb_philo = ft_atoi(argv[1]);
	env->time_die = ft_atoi(argv[2]);
	env->time_eat = ft_atoi(argv[3]);
	env->time_sleep = ft_atoi(argv[4]);
	env->anyone_died = 0;
	env->all_finished_eat = 0;
	env->nb_eat = -1;
	if (argc == 6)
	{
		env->nb_eat = ft_atoi(argv[5]);
		if (env->nb_eat <= 0)
			return (0);
	}
	return (1);
}

int	init_env(int argc, char **argv, t_env *env)
{
	if (!init_vars(argc, argv, env))
		return (0);
	if (!init_philo(env))
		return (0);
	if (!init_mutex(env))
		return (0);
	return (1);
}
