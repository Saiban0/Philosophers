/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:13:43 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/09 19:34:43 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held != 0)
		put_back_forks(main, philo);
	else
	{
		gettimeofday(&time, NULL);
		ft_printf("%d %d is sleeping\n", (time.tv_sec / 1000), philo->id);
		usleep(main->time_to_eat);
	}
}
