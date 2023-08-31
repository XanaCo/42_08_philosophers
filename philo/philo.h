/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:58:16 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 16:08:56 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
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

typedef struct s_phi
{
	int				id;
	pthread_t		th;
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
	struct timeval	t_start;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	died_mtx;
	int				died;
	pthread_mutex_t	end_mtx;
	int				end;
	pthread_mutex_t	fin_mtx;
	int				n_finished;
}		t_data;

/*CHECK AND STOCK*/
void			check_and_stock(t_data *data, char **argv);

/*THREADS*/
void			create_threads(t_data *data);
void			*philo_start(void *th_data);
int				flag_end(t_phi *philo);
int				check_philosophers_status(t_phi *philo);
int				waiting_and_checking(int time, t_phi *philo);

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
