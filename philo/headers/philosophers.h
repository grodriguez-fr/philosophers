/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:56:20 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/06 14:15:57 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				times_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	struct s_env	*env;
	pthread_t		thread_id;
	pthread_mutex_t	*meal;
}	t_philo;

typedef struct s_env
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				anyone_died;
	int				all_finished_eat;
	int				*fork_values;
	long long		time_start;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*end_simulation;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
}	t_env;

int			ft_atoi(const char *str);
int			init_env(int argc, char **argv, t_env *env);
int			start_thread(t_env *env);
void		ft_putstr_err(const char *str);
void		exit_philo(t_env *env, int exit_code);
void		print_log(t_env *env, t_philo *phi, const char *action);
void		checked_sleep(long long time, t_env *env);
long long	get_time(void);
void		*routine(void *philo_void);
#endif
