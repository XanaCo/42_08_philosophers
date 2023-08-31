/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 18:01:31 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
*/
void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	if (sem_wait(data->stop) != -1)
	{
		if (data->n_meals)
		{	
			while (i < data->n_phi)
			{	
				sem_post(data->end);
				i++;
			}
		}
	}
	return (NULL);
}

/*
*/
void	*check_end(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	if (data->n_meals)
	{
		while (i < data->n_phi)
		{	
			sem_wait(data->end);
			i++;
		}
		sem_post(data->stop);
	}
	return (NULL);
}

/*
This is basically a sleep function with a check in the middle
*/
void	waiting_and_checking(int time, t_phi *philo)
{
	unsigned long	t;
	struct timeval	now;
	struct timeval	start;

	t = 0;
	gettimeofday(&start, NULL);
	while (t <= (unsigned long)time)
	{
		flag_end(philo);
		usleep (500);
		gettimeofday(&now, NULL);
		t = time_passed(start, now);
	}
}

/*
*/
void	flag_end(t_phi *philo)
{
	struct timeval	now;
	unsigned long	tp;

	gettimeofday(&now, NULL);
	tp = time_passed(philo->t_last_meal, now);
	if (tp > (unsigned long)philo->data->t_die)
	{
		philo->stop = 1;
		print_death(philo, DIED, WHITE);
		sem_post(philo->data->stop);
	}
}
