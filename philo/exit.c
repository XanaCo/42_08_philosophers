/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 13:41:44 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
We exit freeing and writing if there are any errors
*/
void	free_and_exit(t_data *data, int error)
{
	if (error != 0)
		error_handling(error);
	free_structure(data, error);
	exit(1);
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
	}
}

/*
As its name states, we free the program structure and we destroy the mutex
*/
void	free_structure(t_data *data, int error)
{
	int	i;

	i = 0;
	if (!error || error == -4)
	{
		while (i < data->n_phi)
		{
			pthread_mutex_destroy(&(data->fork_mtx[i]));
			i++;
		}
		pthread_mutex_destroy(&(data->died_mtx));
		pthread_mutex_destroy(&(data->end_mtx));
	}
	if (data->phi)
		free(data->phi);
	if (data->fork_mtx)
		free(data->fork_mtx);
}
