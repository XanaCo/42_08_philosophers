/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:27:05 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 18:02:07 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
This routine function will firstly check if there is only one philo or if the
time to die is too short. Then it starts the eating routine : take forks, eat 
(while cheking if philo dies) and release forks.
*/
void	eating(t_phi *philo)
{
	if (philo->data->n_phi == 1)
	{	
		philo->stop = 1;
		print_status(philo, FORK, YELLOW);
		print_status(philo, THINK, CYAN);
		usleep(philo->data->t_die * 1000);
		print_death(philo, DIED, WHITE);
		sem_post(philo->data->stop);
	}
	if (philo->stop)
		return ;
	picked_forks(philo);
	print_status(philo, EAT, RED);
	gettimeofday(&philo->t_last_meal, NULL);
	waiting_and_checking(philo->data->t_eat, philo);
	philo->meals++;
	released_forks(philo);
	if (philo->data->n_meals && philo->meals == philo->data->n_meals)
		sem_post(philo->data->end);
}

/*
*/
void	picked_forks(t_phi *philo)
{
	if (sem_wait(philo->data->forks))
		free_and_exit(philo->data, 0);
	print_status(philo, FORK, YELLOW);
	if (sem_wait(philo->data->forks))
		free_and_exit(philo->data, 0);
	print_status(philo, FORK, YELLOW);
}

/*
*/
void	released_forks(t_phi *philo)
{
	if (sem_post(philo->data->forks))
		free_and_exit(philo->data, 0);
	if (sem_post(philo->data->forks))
		free_and_exit(philo->data, 0);
}

/*
Philo sleeps while checking time_to_die
*/
void	sleeping(t_phi *philo)
{
	if (philo->stop)
		return ;
	print_status(philo, SLEEP, GREEN);
	waiting_and_checking(philo->data->t_sleep, philo);
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
	if (t_think > 0)
		waiting_and_checking(t_think, philo);
}
