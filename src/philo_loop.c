/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:33:26 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/04 20:37:02 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	limited_routine(t_main *main, int i)
{
	while (has_every_philo_eaten(main))
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
		main->time++;
	}
}

void	*philosopher_routine(void *data)
{
	t_main	*main;

	main = (t_main *)data;
	
	return (main);
}

void	philo_loop(t_main *main)
{
	int	i;

	i = 0;
	if (main->number_of_times_each_philosophers_must_eat == -1)
	{
		while (!is_a_philo_dead(main->philo_list))
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
			main->time++;
		}
	}
	else
		limited_routine(main, i);
}
