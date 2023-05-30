#include "philosophers.h"

int main(int argc, char **argv)
{
	t_env env;

    if (!init_env(argc, argv, &env))
        exit_philo(&env, 1);
    start_thread(&env);
	exit_philo(&env, 0);
    return (0);
}
