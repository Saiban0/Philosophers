/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:29:51 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/26 20:56:40 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_main *main, t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&main->mutex);
	gettimeofday(&time, NULL);
	ft_printf("%u %u is thinking\n", ((time.tv_sec * 1000)
			+ (time.tv_usec / 1000)), philo->id);
	pthread_mutex_unlock(&main->mutex);
	usleep(main->time_to_eat * 1000);
}
