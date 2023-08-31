/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 13:53:43 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
PHILOSOPHERS WITH THREADS AND MUTEX

• Each philo is represented by a thread
• There is one fork between each two philosophers
• We must protect the forks status in memory to avoid fork-stealing

Allowed functions :
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/
int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 6 && argc != 5)
		free_and_exit(&data, -1);
	check_and_stock(&data, argv);
	create_threads(&data);
	free_structure(&data, 0);
	return (EXIT_SUCCESS);
}
