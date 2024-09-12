/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:36:48 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/12 17:34:12 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_a_philo_dead(t_main *main)
{
	int				i;
	struct timeval	time;

	i = -1;
	while (++i < main->number_of_philosophers)
	{
		pthread_mutex_lock(&main->philo_list[i]->mutex);
		if (!main->philo_list[i]->alive)
		{
			gettimeofday(&time, NULL);
			ft_printf("%u %u died\n", ((time.tv_sec * 1000)
					+ (time.tv_usec / 1000)), main->philo_list[i]->id);
			pthread_mutex_unlock(&main->philo_list[i]->mutex);
			error_management(e_philo_died, main);
			return (1);
		}
		pthread_mutex_unlock(&main->philo_list[i]->mutex);
	}
	return (0);
}

int	has_every_philo_eaten(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->number_of_philosophers)
	{
		if (main->philo_list[i]->times_eaten
			>= main->number_of_times_each_philosophers_must_eat)
			i++;
		else
			return (1);
	}
	return (0);
}

void	philo_end(t_main *main)
{
	int	i;

	i = 0;
	while (main->philo_list[i])
	{
		pthread_join(main->philo_list[i]->thread, NULL);
		i++;
	}
}

void	time_message(t_philo *philo, char type)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (type == 'f')
		ft_printf("%u %u has taken a fork\n", ((time.tv_sec * 1000)
				+ (time.tv_usec / 1000)), philo->id);
	if (type == 'e')
		ft_printf("%u %u is eating\n", ((time.tv_sec * 1000)
				+ (time.tv_usec / 1000)), philo->id);
	if (type == 's')
		ft_printf("%u %u is sleeping\n", ((time.tv_sec * 1000)
				+ (time.tv_usec / 1000)), philo->id);
	if (type == 't')
		ft_printf("%u %u is thinking\n", ((time.tv_sec * 1000)
				+ (time.tv_usec / 1000)), philo->id);
}
