/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:47:32 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/01 10:47:57 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	print_log(t_env *env, t_philo *philo, const char *action)
{
	if (env->anyone_died == 0 && env->all_finished_eat == 0)
	{
		pthread_mutex_lock(env->writing);
		printf("%llu %d %s\n", get_time() - env->time_start, philo->id, action);
		pthread_mutex_unlock(env->writing);
	}
}

void	ft_putstr_err(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write (1, str, i);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				res;
	int				sign;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + sign * (str[i++] - '0');
	return (res);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	checked_sleep(long long time, t_env *env)
{
	long long	i;

	i = get_time();
	while (!(env->anyone_died) && !(env->all_finished_eat))
	{
		if ((get_time() - i) >= time)
			break ;
		usleep(50);
	}
}
