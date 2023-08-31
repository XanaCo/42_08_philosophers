/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:27:05 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 17:15:18 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
This routine function will firstly check if there is only one philo or if the
time to die is too short. Then it starts the eating routine : take forks, eat 
(while cheking if philo dies) and release forks.
*/
void	eating(t_phi *philo)
{
	if (philo->data->n_phi == 1)
	{	
		print_status(philo, FORK, YELLOW);
		print_status(philo, THINK, CYAN);
		usleep(philo->data->t_die * 1000);
		print_death(philo, DIED, WHITE);
		philo->stop = 1;
	}
	if (philo->stop)
		return ;
	picked_forks(philo);
	print_status(philo, EAT, RED);
	gettimeofday(&philo->t_last_meal, NULL);
	if (waiting_and_checking(philo->data->t_eat, philo))
		philo->stop = 1;
	philo->meals++;
	released_forks(philo);
	if (philo->meals == philo->data->n_meals)
	{
		pthread_mutex_lock(&(philo->data->end_mtx));
		philo->data->end++;
		pthread_mutex_unlock(&(philo->data->end_mtx));
	}
}

/*
With the mutex, we check the value of the forks while protecting them
*/
void	picked_forks(t_phi *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(philo->data->fork_mtx[philo->id - 1]));
		print_status(philo, FORK, YELLOW);
		if (philo->id != (philo->data->n_phi) || philo->id == 1)
			pthread_mutex_lock(&(philo->data->fork_mtx[philo->id]));
		else
			pthread_mutex_lock(&(philo->data->fork_mtx[0]));
		print_status(philo, FORK, YELLOW);
	}
	else
	{
		if (philo->id != (philo->data->n_phi) || philo->id == 1)
			pthread_mutex_lock(&(philo->data->fork_mtx[philo->id]));
		else
			pthread_mutex_lock(&(philo->data->fork_mtx[0]));
		print_status(philo, FORK, YELLOW);
		pthread_mutex_lock(&(philo->data->fork_mtx[philo->id - 1]));
		print_status(philo, FORK, YELLOW);
	}
}

/*
With the mutex, we check the value of the forks while protecting them
*/
void	released_forks(t_phi *philo)
{
	pthread_mutex_unlock(&(philo->data->fork_mtx[philo->id - 1]));
	if (philo->id != (philo->data->n_phi) || philo->id == 1)
		pthread_mutex_unlock(&(philo->data->fork_mtx[philo->id]));
	else
		pthread_mutex_unlock(&(philo->data->fork_mtx[0]));
}

/*
Philo sleeps while checking time_to_die
*/
void	sleeping(t_phi *philo)
{
	if (philo->stop)
		return ;
	print_status(philo, SLEEP, GREEN);
	if (waiting_and_checking(philo->data->t_sleep, philo))
		philo->stop = 1;
}

/*
Philo thinks an elastic time (which depends on the argument values)
while checking if we die
*/
void	thinking(t_phi *philo)
{
	int	t_think;

	t_think = 1;
	if (philo->stop)
		return ;
	print_status(philo, THINK, CYAN);
	if (!philo->meals)
	{
		if ((philo->data->n_phi % 2) && philo->id == 1)
			t_think = philo->data->t_eat * 2;
		else if (philo->id % 2)
			t_think = philo->data->t_eat;
	}
	else if ((philo->data->n_phi % 2) && philo->id == 2)
		t_think = philo->data->t_eat;
	else if (!(philo->data->n_phi % 2))
		t_think = philo->data->t_eat - philo->data->t_sleep;
	if (t_think > 0 && waiting_and_checking(t_think, philo))
		philo->stop = 1;
}
