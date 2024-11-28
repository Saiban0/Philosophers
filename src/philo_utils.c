/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:36:48 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/28 16:23:15 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_a_philo_dead(t_main *main)
{
	int				i;

	i = -1;
	while (++i < main->number_of_philosophers)
	{
		pthread_mutex_lock(&main->philo_list[i]->mutex);
		if (!main->philo_list[i]->alive)
		{
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
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	while (++i < main->number_of_philosophers && main->philo_max_eat != -1)
	{
		pthread_mutex_lock(&main->philo_list[i]->mutex);
		if (finished_eating == main->number_of_philosophers)
		{
			ft_printf("HERE\n");
			return (1);
		}
		if (main->philo_list[i]->times_eaten >= main->philo_max_eat)
			finished_eating++;
		pthread_mutex_unlock(&main->philo_list[i]->mutex);
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
	if (type == 'g')
		ft_printf("%u %u has put down his forks\n", ((time.tv_sec * 1000)
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

void	philo_print(t_philo *philo, char *message)
{
	struct timeval	time;
	int				current_time;

	pthread_mutex_lock(&philo->main->mutex);
	gettimeofday(&time, NULL);
	current_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000))
		- philo->main->start_time;
	ft_printf("%d %d %s", current_time, philo->id, message);
	pthread_mutex_unlock(&philo->main->mutex);
}
