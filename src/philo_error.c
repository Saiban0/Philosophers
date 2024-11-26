/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:07:49 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/26 21:32:52 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_fork_mutexes_and_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosophers)
	{
		pthread_join(main->philo_list[i]->thread, NULL);
		pthread_mutex_destroy(&main->philo_list[i]->mutex);
		pthread_mutex_destroy(&main->philo_list[i]->print_mutex);
		pthread_mutex_destroy(&main->philo_list[i]->fork_left);
		pthread_mutex_destroy(&main->philo_list[i]->fork_right);
		i++;
	}
	pthread_mutex_destroy(&main->mutex);
}

static void	error_free(t_main *main)
{
	if (main->philo_list)
	{
		destroy_fork_mutexes_and_threads(main);
		ft_free_double_array((void **)main->philo_list);
	}
	free(main);
}

void	error_management(int error_code, t_main *main)
{
	// pthread_mutex_lock(&main->mutex);
	if (error_code == 1)
		ft_putstr_fd("philosophers: init failure \n", STDERR_FILENO);
	if (error_code == 2)
		ft_putstr_fd("philosophers: a philo died \n", STDERR_FILENO);
	if (error_code == 3)
		ft_putstr_fd("philosophers: must run with either 4 or 5 arguments \n",
			STDERR_FILENO);
	error_free(main);
	exit(0);
}
