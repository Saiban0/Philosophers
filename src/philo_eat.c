/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:20:42 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/28 16:21:55 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	grab_forks_last_philo(t_main *main, t_philo *philo)
// {
// 	if (philo->forks_held < 2)
// 	{
// 		pthread_mutex_lock(&philo->mutex);
// 		if (main->fork_list[philo->id - 1]->available
// 			&& main->fork_list[0]->available)
// 		{
// 			pthread_mutex_lock(&main->fork_list[philo->id - 1]->mutex);
// 			pthread_mutex_lock(&main->fork_list[0]->mutex);
// 			time_message(philo, 'f');
// 			time_message(philo, 'f');
// 			main->fork_list[philo->id - 1]->available = 0;
// 			main->fork_list[philo->id - 1]->used_by = philo->id;
// 			main->fork_list[0]->available = 0;
// 			main->fork_list[0]->used_by = philo->id;
// 			philo->forks_held = 2;
// 			pthread_mutex_unlock(&philo->mutex);
// 			philo_eat(main, philo);
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&philo->mutex);
// 		}
// 	}
// }

static void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->print_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_left);
		philo_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->fork_right);
		philo_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->fork_right);
		philo_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->fork_left);
		philo_print(philo, "has taken a fork\n");
	}
	pthread_mutex_unlock(&philo->main->print_mutex);
}

void	put_back_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(&philo->fork_right);
	philo_print(philo, "has put down his forks\n");
}

void	philo_eat(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (main->philo_max_eat != -1
		&& philo->times_eaten
		>= main->philo_max_eat)
		return ;
	// if (philo->id != main->number_of_philosophers)
	grab_forks(philo);
	// else
		// grab_forks_last_philo(main, philo);
	pthread_mutex_lock(&philo->mutex);
	philo_print(philo, "is eating\n");
	usleep(main->time_to_eat * 1000);
	gettimeofday(&time, NULL);
	philo->last_meal = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	philo->times_eaten++;
	put_back_forks(philo);
	pthread_mutex_unlock(&philo->mutex);
}
