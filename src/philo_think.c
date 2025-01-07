/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:29:51 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/28 15:56:50 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_main *main, t_philo *philo)
{
	philo_print(philo, "is thinking\n");
	usleep(main->time_to_eat * 1000);
}
