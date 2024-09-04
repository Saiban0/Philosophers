/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:07:49 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/04 20:00:16 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	error_free(t_main *main)
{
	if (main->philo_list)
		ft_free_double_array((void **)main->philo_list);
	if (main->fork_list)
		ft_free_double_array((void **)main->fork_list);
	free(main);
}

void	error_management(int error_code, t_main *main)
{
	if (error_code == 0)
		ft_putstr_fd("philosophers: no error code \n", STDERR_FILENO);
	if (error_code == 1)
		ft_putstr_fd("philosophers: init failure \n", STDERR_FILENO);
	error_free(main);
	exit(0);
}
