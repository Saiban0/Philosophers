/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:29:51 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/05 19:21:05 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held != 0)
		put_back_forks(main, philo);
	else
	{
		gettimeofday(&time, NULL);
		ft_printf("%d %d is\n", time.tv_usec, philo->id);
		usleep(main->time_to_eat);
	}
}
