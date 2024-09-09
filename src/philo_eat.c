/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:20:42 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/09 19:37:01 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	grab_forks_last_philo(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held < 2)
	{
		if (main->fork_list[philo->id - 1]->available
			&& main->fork_list[0]->available)
		{
			pthread_mutex_lock(&main->fork_list[philo->id - 1]->mutex);
			pthread_mutex_lock(&main->fork_list[0]->mutex);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", (time.tv_sec / 1000), philo->id);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", (time.tv_sec / 1000), philo->id);
			main->fork_list[philo->id - 1]->available = 0;
			main->fork_list[philo->id - 1]->used_by = main->tmp;
			main->fork_list[0]->available = 0;
			main->fork_list[0]->used_by = main->tmp;
			philo->forks_held = 2;
		}
	}
}

static void	grab_forks(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (philo->forks_held < 2)
	{
		if (main->fork_list[philo->id - 1]->available
			&& main->fork_list[philo->id]->available)
		{
			pthread_mutex_lock(&main->fork_list[philo->id -1]->mutex);
			pthread_mutex_lock(&main->fork_list[philo->id]->mutex);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", (time.tv_sec / 1000),
				philo->id);
			gettimeofday(&time, NULL);
			ft_printf("%d %d has taken a fork\n", (time.tv_sec / 1000),
				philo->id);
			main->fork_list[philo->id - 1]->available = 0;
			main->fork_list[philo->id - 1]->used_by = main->tmp;
			main->fork_list[philo->id]->available = 0;
			main->fork_list[philo->id]->used_by = main->tmp;
			philo->forks_held = 2;
			philo_eat(main, philo);
		}
	}
}

void	put_back_forks(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
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

void	philo_eat(t_main *main, t_philo *philo)
{
	struct timeval	time;

	if (main->number_of_times_each_philosophers_must_eat != -1 &&
		philo->times_eaten >= main->number_of_times_each_philosophers_must_eat)
	{
		return ;
	}
	if (philo->forks_held == 2)
	{
		gettimeofday(&time, NULL);
		ft_printf("%d %d is eating\n", (time.tv_sec / 1000), philo->id);
		usleep(main->time_to_eat);
		philo->last_meal = (time.tv_sec / 1000);
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
