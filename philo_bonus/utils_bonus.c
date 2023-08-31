/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/19 20:23:57 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
A pimped atoi with a variation to avoid signed variables and with freeing
and exiting if something goes wrong
*/
int	ft_atoi_phi(t_data *data, const char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] == '\f' || nptr[i] == '\t' || nptr[i] == ' '
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			free_and_exit(data, -2);
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	if (!result || nptr[i] || result > INT_MAX)
		free_and_exit(data, -2);
	return ((int)result);
}

/*
This function checks the time passed from start to now in ms
*/
unsigned long	time_passed(struct timeval t_start, struct timeval t_now)
{
	unsigned long	tp;

	tp = (t_now.tv_sec - t_start.tv_sec) * 1000;
	tp += ((t_now.tv_usec - t_start.tv_usec) / 1000);
	return (tp);
}

/*
This will print the message status when a philo changes
*/
void	print_status(t_phi *philo, char *msg, char *color)
{
	unsigned long	t_stamp;
	struct timeval	now;

	gettimeofday(&now, NULL);
	t_stamp = time_passed(philo->data->t_start, now);
	sem_wait(philo->data->print);
	printf("%s%ld %d %s\e[0m\n", color, t_stamp, philo->id, msg);
	sem_post(philo->data->print);
}

/*
A variation of print_status, will print the death status. 
Only needed when really sure of the death of a philosopher
*/
void	print_death(t_phi *philo, char *msg, char *color)
{
	unsigned long	t_stamp;
	struct timeval	now;

	gettimeofday(&now, NULL);
	t_stamp = time_passed(philo->data->t_start, now);
	sem_wait(philo->data->print);
	printf("%s%ld %d %s\e[0m\n", color, t_stamp, philo->id, msg);
}
