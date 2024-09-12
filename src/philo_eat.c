/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:20:42 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/12 17:52:55 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	grab_forks_last_philo(t_main *main, t_philo *philo)
{
	if (philo->forks_held < 2)
	{
		pthread_mutex_lock(&philo->mutex);
		if (main->fork_list[philo->id - 1]->available
			&& main->fork_list[0]->available)
		{
			pthread_mutex_lock(&main->fork_list[philo->id - 1]->mutex);
			pthread_mutex_lock(&main->fork_list[0]->mutex);
			time_message(philo, 'f');
			time_message(philo, 'f');
			main->fork_list[philo->id - 1]->available = 0;
			main->fork_list[philo->id - 1]->used_by = philo->id;
			main->fork_list[0]->available = 0;
			main->fork_list[0]->used_by = philo->id;
			philo->forks_held = 2;
			pthread_mutex_unlock(&philo->mutex);
			philo_eat(main, philo);
		}
		else
		{
			pthread_mutex_lock(&philo->mutex);
		}
	}
}

static void	grab_forks(t_main *main, t_philo *philo)
{
	if (philo->forks_held < 2)
	{
		pthread_mutex_lock(&main->fork_list[philo->id - 1]->mutex);
		pthread_mutex_lock(&main->fork_list[philo->id]->mutex);
		pthread_mutex_lock(&philo->mutex);
		if (main->fork_list[philo->id - 1]->available
			&& main->fork_list[philo->id]->available)
		{
			time_message(philo, 'f');
			time_message(philo, 'f');
			main->fork_list[philo->id - 1]->available = 0;
			main->fork_list[philo->id - 1]->used_by = philo->id;
			main->fork_list[philo->id]->available = 0;
			main->fork_list[philo->id]->used_by = philo->id;
			philo->forks_held = 2;
			pthread_mutex_unlock(&philo->mutex);
			philo_eat(main, philo);
		}
		else
		{
			pthread_mutex_unlock(&main->fork_list[philo->id - 1]->mutex);
			pthread_mutex_unlock(&main->fork_list[philo->id]->mutex);
			pthread_mutex_unlock(&philo->mutex);
		}
	}
}

void	put_back_forks(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	while (main->fork_list[i] && philo->forks_held > 0)
	{
		pthread_mutex_lock(&philo->mutex);
		if (main->fork_list[i]->used_by == philo->id)
		{
			main->fork_list[i]->available = 1;
			main->fork_list[i]->used_by = -1;
			philo->forks_held--;
			pthread_mutex_unlock(&main->fork_list[i]->mutex);
		}
		pthread_mutex_unlock(&philo->mutex);
		i++;
	}
}

void	philo_eat(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (main->number_of_times_each_philosophers_must_eat != -1
		&& philo->times_eaten
		>= main->number_of_times_each_philosophers_must_eat)
		return ;
	if (philo->forks_held == 2)
	{
		pthread_mutex_lock(&philo->mutex);
		time_message(philo, 'e');
		usleep(main->time_to_eat * 1000);
		gettimeofday(&time, NULL);
		philo->last_meal = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->mutex);
		put_back_forks(main, philo);
	}
	else
	{
		if (philo->id != main->number_of_philosophers)
			grab_forks(main, philo);
		else
			grab_forks_last_philo(main, philo);
	}
}
