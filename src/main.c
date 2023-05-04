#include "philosophers.h"

#include <stdio.h>
int main(int argc, char **argv)
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;


	if (argc != 5)
		return (ft_putstr_err("Wrong arg number, usage : ./philo [nb] [time_die] [time_eat] [time_sleep]"), 1);
	nb_philo = ft_atoi(argv[1]);	
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	printf("%d\n%d\n%d\n%d\n", nb_philo, time_to_die, time_to_eat, time_to_sleep);
	return (0);
}
