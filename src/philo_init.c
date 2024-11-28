/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:25:44 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/28 15:50:27 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*create_philo(int id, t_main *main)
{
	t_philo			*new;
	struct timeval	time;

	new = malloc(sizeof(t_philo));
	new->id = id + 1;
	new->alive = 1;
	new->times_eaten = 0;
	new->forks_held = 0;
	gettimeofday(&time, NULL);
	new->last_meal = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_init(&new->mutex, NULL);
	new->main = main;
	return (new);
}

int	create_philo_list(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosophers)
	{
		main->philo_list[i] = create_philo(i, main);
		i++;
	}
	main->philo_list[main->number_of_philosophers] = NULL;
	if (i != main->number_of_philosophers)
		return (1);
	return (0);
}

// static t_fork	*create_fork(int id)
// {
// 	t_fork	*new;

// 	new = malloc(sizeof(t_fork));
// 	new->id = id + 1;
// 	new->available = 1;
// 	new->used_by = -1;
// 	pthread_mutex_init(&new->mutex, NULL);
// 	return (new);
// }

// int	create_fork_list(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while (i < main->number_of_philosophers)
// 	{
// 		main->fork_list[i] = create_fork(i);
// 		i++;
// 	}
// 	main->fork_list[i + 1] = NULL;
// 	if (i != main->number_of_philosophers)
// 		return (1);
// 	return (0);
// }

int	init_philo(t_main *main, int argc, char **argv)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	main->number_of_philosophers = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	main->philo_max_eat = -1;
	main->philo_list = malloc(main->number_of_philosophers * sizeof(t_philo *));
	main->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	// main->fork_list = malloc(main->number_of_philosophers * sizeof(t_fork *));
	pthread_mutex_init(&main->mutex, NULL);
	pthread_mutex_init(&main->print_mutex, NULL);
	if (!main->philo_list || create_philo_list(main))
		error_management(e_init_failure, main);
	if (argc == 6)
		main->philo_max_eat = ft_atoi(argv[5]);
	return (0);
}
