/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:20:42 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/04 20:57:15 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	grab_fork(t_main *main)
{
	int	i;
	int	id;

	i = 0;
	id = main->tmp;
	if (main->philo_list[id]->forks_held < 2)
	{
		while (main->fork_list[i] && main->philo_list[id]->forks_held < 2)
		{
			if (main->fork_list[i]->available)
			{
				main->fork_list[i]->available = 0;
				main->fork_list[i]->used_by = main->tmp;
				main->philo_list[id]->forks_held++;
			}
			i++;
		}
		if (main->philo_list[id]->forks_held == 2)
			return (0);
	}
	return (1);
}

int	put_back_fork(t_main *main)
{
	int	i;
	int	id;

	i = 0;
	id = main->tmp;
	if (main->philo_list[id]->forks_held == 2)
	{
		while (main->fork_list[i] && main->philo_list[id]->forks_held > 0)
		{
			if (main->fork_list[i]->used_by == id)
			{
				main->fork_list[i]->available = 1;
				main->fork_list[i]->used_by = -1;
				main->philo_list[id]->forks_held--;
			}
			i++;
		}
		if (main->philo_list[id]->forks_held == 0)
			return (0);
	}
	return (1);
}
