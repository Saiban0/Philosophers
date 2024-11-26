/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:20:42 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/26 21:31:48 by bchedru          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->print_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_left);
		time_message(philo, 'f');
		pthread_mutex_lock(&philo->fork_right);
		time_message(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&philo->fork_right);
		time_message(philo, 'f');
		pthread_mutex_lock(&philo->fork_left);
		time_message(philo, 'f');
	}
	pthread_mutex_unlock(&philo->print_mutex);
}

void	put_back_forks(t_main *main, t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(&philo->fork_right);
	pthread_mutex_lock(&main->mutex);
	time_message(philo, 'g');
	pthread_mutex_unlock(&main->mutex);
}

void	philo_eat(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (main->number_of_times_each_philosophers_must_eat != -1
		&& philo->times_eaten
		>= main->number_of_times_each_philosophers_must_eat)
		return ;
	if (philo->id != main->number_of_philosophers)
		grab_forks(philo);
	// else
		// grab_forks_last_philo(main, philo);
	pthread_mutex_lock(&philo->mutex);
	time_message(philo, 'e');
	usleep(main->time_to_eat * 1000);
	gettimeofday(&time, NULL);
	philo->last_meal = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	philo->times_eaten++;
	put_back_forks(main, philo);
	pthread_mutex_unlock(&philo->mutex);
}
