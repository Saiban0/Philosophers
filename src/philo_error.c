/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:07:49 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/09 19:41:07 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_fork_mutexes_and_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosophers)
	{
		put_back_forks(main, main->philo_list[i]);
		pthread_mutex_destroy(&main->fork_list[i]->mutex);
		pthread_mutex_destroy(&main->philo_list[i]->mutex);
		pthread_join(main->philo_list[i]->thread, NULL);
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
	if (main->fork_list)
		ft_free_double_array((void **)main->fork_list);
	free(main);
}

void	error_management(int error_code, t_main *main)
{
	if (error_code == 0)
		ft_putstr_fd("philosophers: no error found \n", STDERR_FILENO);
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
