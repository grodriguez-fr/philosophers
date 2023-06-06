/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:47:20 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/01 10:47:22 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (!init_env(argc, argv, &env))
		exit_philo(&env, 1);
	start_thread(&env);
    printf("FIN !\n");
	exit_philo(&env, 0);
	return (0);
}
