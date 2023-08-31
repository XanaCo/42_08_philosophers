/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/20 18:06:54 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
PHILOSOPHERS WITH PROCESSES AND SEMAPHORES

• All forks are at the centre of the table
• The forks have not a status in memory, its number is protected by semaphores
• Each philo is represented by a different process
• Main process should not be a philosopher

Allowed functions :
memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
*/
int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 6 && argc != 5)
		free_and_exit(&data, -1);
	check_and_stock(&data, argv);
	create_philos(&data);
	create_threads(&data);
	free_structure(&data, 0);
	return (EXIT_SUCCESS);
}

// one process per philo
// a semaphore should represent the number of forks
// no orphan processes should be present
// output protected against multiple access to avoid a scrambled display
//the death of a philo is verified and there is a semaphore to prevent
// a philo from dying and eating at the same time