/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/23 16:20:47 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
This function will create the threads, start the routine and check if there 
are errors and end the threads when we finished
*/
void	create_threads(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_phi)
	{	
		if (pthread_create(&data->phi[i].th, NULL, &philo_start, &data->phi[i]))
			free_and_exit(data, -4);
		i++;
	}
	i = 0;
	while (i < data->n_phi)
	{
		if (pthread_join(data->phi[i++].th, NULL))
			free_and_exit(data, -4);
	}
}

/*
This function will start the routine for each thread
and check its status at each turn
*/
void	*philo_start(void *th_data)
{
	t_phi	*philo;

	philo = (t_phi *)th_data;
	if (philo->id % 2 != 0 && philo->data->n_phi > 1)
		thinking(philo);
	while (!check_philosophers_status(philo))
	{	
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

/*
With the mutex, each thread checks if all meals are taken or if somebody died
*/
int	check_philosophers_status(t_phi *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&(philo->data->died_mtx));
	pthread_mutex_lock(&(philo->data->end_mtx));
	if (philo->data->died || philo->stop
		|| (philo->data->n_meals && philo->data->end == philo->data->n_phi))
		status = 1;
	pthread_mutex_unlock(&(philo->data->end_mtx));
	pthread_mutex_unlock(&(philo->data->died_mtx));
	return (status);
}

/*
This is basically a sleep function with a check in the middle
*/
int	waiting_and_checking(int time, t_phi *philo)
{
	unsigned long	t;
	struct timeval	now;
	struct timeval	start;

	t = 0;
	gettimeofday(&start, NULL);
	while (t <= (unsigned long)time)
	{
		if (flag_end(philo))
			return (1);
		usleep (500);
		gettimeofday(&now, NULL);
		t = time_passed(start, now);
	}
	return (0);
}

/*
This function will flag the 'end' or 'died' variable in the main structure
*/
int	flag_end(t_phi *philo)
{
	struct timeval	now;
	unsigned long	tp;
	int				flag;

	flag = 0;
	gettimeofday(&now, NULL);
	tp = time_passed(philo->t_last_meal, now);
	if (tp > (unsigned long)philo->data->t_die)
	{
		pthread_mutex_lock(&(philo->data->died_mtx));
		philo->data->died += 1;
		if (philo->data->died == 1)
			print_death(philo, DIED, WHITE);
		flag += philo->data->died;
		pthread_mutex_unlock(&(philo->data->died_mtx));
	}
	if (philo->data->n_meals)
	{	
		pthread_mutex_lock(&(philo->data->end_mtx));
		if (philo->data->end == philo->data->n_phi)
			flag += philo->data->end;
		pthread_mutex_unlock(&(philo->data->end_mtx));
	}
	return (flag);
}
