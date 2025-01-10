/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:33:25 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/10 20:34:55 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_get_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex_main);
	print_error_msg(e_gettime);
	philo->last_meal.tv_usec += 9999;
	philo->last_meal.tv_usec += 9999;
	philo->main->running = 0;
	pthread_mutex_unlock(&philo->main->mutex_main);
	pthread_mutex_unlock(&philo->update_time);
	return (0);
}
