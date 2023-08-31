/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 18:03:09 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
We exit freeing and writing if there are any errors
*/
void	free_and_exit(t_data *data, int error)
{
	if (error != 0)
		error_handling(error);
	free_structure(data, error);
	exit(EXIT_FAILURE);
}

/*
We check which error we had and write it
*/
void	error_handling(int error)
{
	if (error < 0)
	{
		if (error == -1)
			printf("Error: Invalid arguments\n");
		if (error == -2)
			printf("Error: Wrong format\n");
		if (error == -3)
			printf("Error: Not enough memory\n");
		if (error == -4)
			printf("Error: Creation / deletion of threads\n");
		if (error == -5)
			printf("Error: Creation / Modification of semaphore failed\n");
	}
}

/*
As its name states, we free the program structure and we destroy the mutex
*/
void	free_structure(t_data *data, int error)
{
	int	i;

	i = 0;
	if (!error)
	{
		while (i < data->n_phi)
		{
			if (data->phi[i].pid != 0)
			{	
				kill(data->phi[i].pid, SIGKILL);
				i++;
			}
		}
		sem_close(data->forks);
		sem_close(data->end);
		sem_close(data->stop);
		sem_close(data->print);
	}
	if (data->phi)
		free(data->phi);
}
