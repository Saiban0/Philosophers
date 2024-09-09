/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:29:51 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/09 19:34:57 by bchedru          ###   ########.fr       */
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
		ft_printf("%d %d is thinking\n", (time.tv_sec / 1000), philo->id);
		usleep(main->time_to_eat);
	}
}
