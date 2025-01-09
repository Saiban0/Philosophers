/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:07:53 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/09 18:43:55 by bchedru          ###   ########.fr       */
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

static int	philo_belly_full(t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	pthread_mutex_lock(&temp->main->mutex_print);
	pthread_mutex_lock(&temp->main->mutex_main);
	if (philo->main->running != -1)
		printf("(TOCHECK) %ldms the philosophers are satiated\n", philo_get_time(philo->main->start_time));
	philo->main->running = -1;
	pthread_mutex_unlock(&temp->main->mutex_print);
	pthread_mutex_unlock(&temp->main->mutex_main);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	philo_take_forks(temp);
	pthread_mutex_lock(&temp->update_time);
	if (gettimeofday(&temp->last_meal, NULL) == -1)
		return (ft_error_get_time(temp));
	pthread_mutex_unlock(&temp->update_time);
	philo_print(temp, PHILO_EATMSG);
	usleep(temp->main->time_to_eat * 1000);
	pthread_mutex_unlock(&temp->fork);
	pthread_mutex_unlock(temp->fork_right);
	if (temp->main->max_eat != -1 && ++temp->times_eaten
		> temp->main->max_eat)
		return (philo_belly_full(temp));
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
		philo->main->running = -1;
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
