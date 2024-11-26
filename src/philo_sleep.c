/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:13:43 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/26 20:57:03 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_main *main, t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&main->mutex);
	gettimeofday(&time, NULL);
	ft_printf("%u %u is sleeping\n", ((time.tv_sec * 1000)
			+ (time.tv_usec / 1000)), philo->id);
	usleep(main->time_to_sleep * 1000);
	pthread_mutex_unlock(&main->mutex);
}
