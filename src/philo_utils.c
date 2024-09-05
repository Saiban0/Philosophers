/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:36:48 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/05 17:59:54 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_a_philo_dead(t_main *main)
{
	int				i;
	struct timeval	time;

	i = -1;
	while (++i < 4)
	{
		if (!main->philo_list[i]->alive)
		{
			gettimeofday(&time, NULL);
			ft_printf("%d %d died\n", time.tv_usec, i);
			error_management(e_philo_died, main);
			return (1);
		}
	}
	return (0);
}

int	has_every_philo_eaten(t_main *main)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (main->philo_list[i]->times_eaten
			== main->number_of_times_each_philosophers_must_eat)
			i++;
		else
			return (1);
	}
	return (0);
}

void	philo_end(t_main *main)
{
	int	i;

	i = 0;
	while (main->philo_list[i])
	{
		pthread_join(main->philo_list[i]->thread, NULL);
		i++;
	}
}
