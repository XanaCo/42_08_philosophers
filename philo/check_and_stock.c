/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 13:42:35 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
We stock the necessary elements in each philo
*/
static void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phi)
	{	
		memset(&data->phi[i], 0, sizeof(t_phi));
		data->phi[i].id = i + 1;
		data->phi[i].data = data;
		data->phi[i].t_last_meal = data->t_start;
		i++;
	}
}

/*
We initiate all mutex in the structure, we check for errors if they fail
*/
static void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phi)
	{	
		if (pthread_mutex_init(&(data->fork_mtx[i]), NULL))
			free_and_exit(data, 0);
		i++;
	}
	if (pthread_mutex_init(&(data->died_mtx), NULL))
		free_and_exit(data, 0);
	if (pthread_mutex_init(&(data->end_mtx), NULL))
		free_and_exit(data, 0);
	if (pthread_mutex_init(&(data->fin_mtx), NULL))
		free_and_exit(data, 0);
}

/*
This function will stock all the arguments, allocate space in memory for
the philo structures, mutex and forks, initiate the mutex and the philos,
exit if there are any errors
*/
void	check_and_stock(t_data *data, char **argv)
{
	data->n_phi = ft_atoi_phi(data, argv[1]);
	if (data->n_phi <= 0)
		free_and_exit(data, -2);
	data->t_die = ft_atoi_phi(data, argv[2]);
	data->t_eat = ft_atoi_phi(data, argv[3]);
	data->t_sleep = ft_atoi_phi(data, argv[4]);
	if (argv[5])
		data->n_meals = ft_atoi_phi(data, argv[5]);
	data->phi = malloc(data->n_phi * sizeof(t_phi));
	if (!data->phi)
		free_and_exit(data, -3);
	data->fork_mtx = malloc(data->n_phi * sizeof(pthread_mutex_t));
	if (!data->fork_mtx)
		free_and_exit(data, -3);
	if (gettimeofday(&data->t_start, NULL))
		free_and_exit(data, -3);
	mutex_init(data);
	philo_init(data);
}
