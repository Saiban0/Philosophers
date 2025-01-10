/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:07:53 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/10 20:48:05 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		philo_print(philo, PHILO_LEFTFORKMSG);
		pthread_mutex_lock(philo->fork_right);
		philo_print(philo, PHILO_RIGHTFORKMSG);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		philo_print(philo, PHILO_RIGHTFORKMSG);
		pthread_mutex_lock(&philo->fork);
		philo_print(philo, PHILO_LEFTFORKMSG);
	}
	return (0);
}

static int	philo_belly_full(t_philo *temp)
{
	t_philo	*philo;

	philo = temp;
	pthread_mutex_lock(&philo->main->mutex_print);
	pthread_mutex_lock(&philo->main->mutex_main);
	if (temp->main->running != 0)
		printf("%ldms the philosophers have eaten enough\n",
			philo_get_time(philo->main->start_time));
	temp->main->running = 0;
	pthread_mutex_unlock(&philo->main->mutex_main);
	pthread_mutex_unlock(&philo->main->mutex_print);
	return (1);
}

int	philo_eat(t_philo *temp)
{
	t_philo	*philo;

	philo = temp;
	philo_take_forks(philo);
	pthread_mutex_lock(&philo->update_time);
	if (gettimeofday(&philo->last_meal, NULL) == -1)
		return (ft_error_get_time(philo));
	pthread_mutex_unlock(&philo->update_time);
	philo_print(philo, PHILO_EATMSG);
	usleep(philo->main->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(&philo->fork);
	if (philo->main->max_meals != -1
		&& ++philo->times_eaten > philo->main->max_meals)
		return (philo_belly_full(philo));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	philo_print(philo, PHILO_SLEEPMSG);
	usleep(philo->main->time_to_sleep * 1000);
	return (0);
}

void	*philo_routine(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	pthread_mutex_lock(&philo->update_time);
	if (gettimeofday(&philo->last_meal, NULL) == -1)
	{
		pthread_mutex_lock(&philo->main->mutex_main);
		philo->main->running = 0;
		print_error_msg(e_gettime);
		pthread_mutex_unlock(&philo->main->mutex_main);
		pthread_mutex_unlock(&philo->update_time);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->update_time);
	while (check_running(philo) == 0)
	{
		if (philo_eat(philo) != 0)
			return (NULL);
		if (philo_sleep(philo) != 0)
			return (NULL);
		philo_print(philo, PHILO_THINKMSG);
	}
	return (NULL);
}
