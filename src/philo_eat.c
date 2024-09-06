/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:20:42 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/06 16:56:45 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	grab_forks(t_main *main, t_philo *philo)
// {
// 	int				i;
// 	struct timeval	time;

// 	i = 0;
// 	if (philo->forks_held < 2)
// 	{
// 		while (main->fork_list[i])
// 		{
// 			if (main->fork_list[i]->available && philo->forks_held < 2)
// 			{
// 				pthread_mutex_lock(&main->fork_list[i]->mutex);
// 				gettimeofday(&time, NULL);
// 				ft_printf("%d %d has taken a fork\n", time.tv_usec, philo->id);
// 				main->fork_list[i]->available = 0;
// 				main->fork_list[i]->used_by = main->tmp;
// 				philo->forks_held++;
// 			}
// 			i++;
// 		}
// 		if (philo->forks_held == 2)
// 			philo_eat(main, philo);
// 	}
// }

static void	grab_forks_last_philo(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held < 2)
	{
		if (main->fork_list[philo->id]->available
			&& main->fork_list[1]->available)
		{
			pthread_mutex_lock(&main->fork_list[philo->id]->mutex);
			pthread_mutex_lock(&main->fork_list[1]->mutex);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", time.tv_usec, philo->id);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", time.tv_usec, philo->id);
			main->fork_list[philo->id]->available = 0;
			main->fork_list[philo->id]->used_by = main->tmp;
			main->fork_list[1]->available = 0;
			main->fork_list[1]->used_by = main->tmp;
			philo->forks_held = 2;
		}
		else
			philo_think(main, philo);
	}
}

static void	grab_forks(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held < 2)
	{
		if (main->fork_list[philo->id]->available
			&& main->fork_list[philo->id + 1]->available)
		{
			ft_printf("saucisse %d\n", philo->id);
			pthread_mutex_lock(&main->fork_list[philo->id]->mutex);
			pthread_mutex_lock(&main->fork_list[philo->id + 1]->mutex);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", time.tv_usec, philo->id);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", time.tv_usec, philo->id);
			main->fork_list[philo->id]->available = 0;
			main->fork_list[philo->id]->used_by = main->tmp;
			main->fork_list[philo->id + 1]->available = 0;
			main->fork_list[philo->id + 1]->used_by = main->tmp;
			philo->forks_held = 2;
			philo_eat(main, philo);
		}
		else
			philo_think(main, philo);
	}
}

void	put_back_forks(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->forks_held == 2)
	{
		while (main->fork_list[i] && philo->forks_held > 0)
		{
			if (main->fork_list[i]->used_by == philo->id)
			{
				pthread_mutex_unlock(&main->fork_list[i]->mutex);
				main->fork_list[i]->available = 1;
				main->fork_list[i]->used_by = -1;
				philo->forks_held--;
			}
			i++;
		}
	}
}

void	philo_eat(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held == 2)
	{
		gettimeofday(&time, NULL);
		ft_printf("%d %d is eating\n", time.tv_usec, philo->id);
		usleep(main->time_to_eat);
		philo->times_eaten++;
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
