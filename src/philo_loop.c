/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:33:26 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/12 17:45:44 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	time_since_last_meal(t_main *main, t_philo *philo)
{
	struct timeval	time;
	int				diff;

	gettimeofday(&time, NULL);
	diff = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - philo->last_meal;
	if (diff > main->time_to_die)
		philo->alive = 0;
}

static void	*limited_routine(void *data)
{
	t_philo	*philo;
	t_main	*main;

	philo = (t_philo *)data;
	main = philo->main;
	while (!is_a_philo_dead(main) && has_every_philo_eaten(main))
	{
		time_since_last_meal(main, philo);
		philo_eat(main, philo);
		philo_sleep(main, philo);
		philo_think(main, philo);
		time_since_last_meal(main, philo);
	}
	return (main);
}

static void	*philosopher_routine(void *data)
{
	t_philo	*philo;
	t_main	*main;

	philo = (t_philo *)data;
	main = philo->main;
	while (!is_a_philo_dead(main))
	{
		time_since_last_meal(main, philo);
		philo_eat(main, philo);
		philo_sleep(main, philo);
		philo_think(main, philo);
		time_since_last_meal(main, philo);
	}
	return (main);
}

void	philo_loop(t_main *main)
{
	int	i;

	i = 0;
	if (main->number_of_times_each_philosophers_must_eat == -1)
	{
		while (i < main->number_of_philosophers)
		{
			pthread_create(&main->philo_list[i]->thread, NULL,
				philosopher_routine, main->philo_list[i]);
			i++;
		}
	}
	else
	{
		while (i < main->number_of_philosophers)
		{
			pthread_create(&main->philo_list[i]->thread, NULL,
				limited_routine, main->philo_list[i]);
			i++;
		}
	}
}
