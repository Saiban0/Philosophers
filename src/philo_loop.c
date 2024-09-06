/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:33:26 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/06 16:55:34 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	limited_routine(t_main *main, int i)
{
	while (has_every_philo_eaten(main) && is_a_philo_dead(main))
	{
		i = 0;
		while (main->philo_list[i])
		{
			if (main->philo_list[i]->alive)
			{
				main->tmp = i;
				philosopher_routine(main);
			}
			i++;
		}
	}
}

void	*philosopher_routine(void *data)
{
	t_main	*maint;

	maint = (t_main *)data;
	pthread_mutex_lock(&maint->philo_list[maint->tmp]->mutex);
	philo_eat(maint, maint->philo_list[maint->tmp]);
	// philo_think(main, main->philo_list[main->tmp]);
	pthread_mutex_unlock(&maint->philo_list[maint->tmp]->mutex);
	return (maint);
}

void	philo_loop(t_main *main)
{
	int	i;

	i = 0;
	if (main->number_of_times_each_philosophers_must_eat == -1)
	{
		while (!is_a_philo_dead(main))
		{
			i = 0;
			while (main->philo_list[i])
			{
				if (main->philo_list[i]->alive)
				{
					main->tmp = i;
					pthread_create(&main->philo_list[i]->thread, NULL,
						philosopher_routine, main);
				}
				i++;
			}
		}
	}
	else
		limited_routine(main, i);
}
