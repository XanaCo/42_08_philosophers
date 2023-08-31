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
void	create_philos(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_phi)
	{
		data->phi[i].pid = fork();
		if (data->phi[i].pid == -1)
			free_and_exit(data, 0);
		if (data->phi[i].pid == 0)
			philo_start(&(data->phi[i]));
		i++;
	}
}

/*
*/
void	create_threads(t_data *data)
{
	if (pthread_create(&data->died_th, NULL, &check_death, (void *)data))
		free_and_exit(data, -4);
	if (pthread_create(&data->end_th, NULL, &check_end, (void *)data))
		free_and_exit(data, -4);
	if (pthread_join(data->died_th, NULL))
		free_and_exit(data, -4);
	if (pthread_join(data->end_th, NULL))
		free_and_exit(data, -4);
}

/*
This function will start the routine for each thread
and check its status at each turn
*/
void	*philo_start(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	if (philo->id % 2 != 0 && philo->data->n_phi > 1)
		thinking(philo);
	while (!philo->stop)
	{	
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
