/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:58:16 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/23 10:16:20 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define CYAN "\033[36m"
# define YELLOW "\033[33m"
# define WHITE "\033[37;1m"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_phi
{
	int				id;
	pid_t			pid;
	int				meals;
	int				stop;
	struct timeval	t_last_meal;
	struct s_data	*data;
}		t_phi;

typedef struct s_data
{
	t_phi			*phi;
	int				n_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	sem_t			*forks;
	sem_t			*end;
	sem_t			*stop;
	sem_t			*print;
	struct timeval	t_start;
	pthread_t		died_th;
	pthread_t		end_th;
}		t_data;

/*CHECK AND STOCK*/
void			check_and_stock(t_data *data, char **argv);

/*THREADS*/
void			create_philos(t_data *data);
void			create_threads(t_data *data);
void			*philo_start(void *arg);

/*CHECK AND FLAG*/
void			*check_death(void *arg);
void			*check_end(void *arg);
void			waiting_and_checking(int time, t_phi *philo);
void			flag_end(t_phi *philo);

/*ROUTINE*/
void			eating(t_phi *philo);
void			picked_forks(t_phi *philo);
void			released_forks(t_phi *philo);
void			sleeping(t_phi *philo);
void			thinking(t_phi *philo);

/*UTILS*/
int				ft_atoi_phi(t_data *data, const char *nptr);
unsigned long	time_passed(struct timeval t_start, struct timeval t_now);
void			print_status(t_phi *philo, char *msg, char *color);
void			print_death(t_phi *philo, char *msg, char *color);

/*EXIT*/
void			free_and_exit(t_data *data, int error);
void			error_handling(int error);
void			free_structure(t_data *data, int error);

#endif
