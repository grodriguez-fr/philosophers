# philosophers

Le problème des philosophes qui mangent, en C avec des threads POSIX et des mutex (cursus 42). Chaque philosophe est un thread, chaque fourchette un mutex, et un moniteur détecte la mort d'un philosophe au plus vite.

```sh
cd philo && make
./philo <nb_philosophes> <temps_mort> <temps_repas> <temps_sommeil> [nb_repas]
./philo 5 800 200 200
```

Les temps sont en millisecondes.
