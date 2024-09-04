/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:25:44 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/04 20:37:01 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*create_philo(int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->id = id;
	new->alive = 1;
	new->times_eaten = 0;
	new->forks_held = 0;
	return (new);
}

int	create_philo_list(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosophers)
	{
		main->philo_list[i] = create_philo(i);
		i++;
	}
	main->philo_list[i] = NULL;
	if (i != main->number_of_philosophers)
		return (1);
	return (0);
}

static t_fork	*create_fork(int id)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	new->id = id;
	new->available = 1;
	new->used_by = -1;
	return (new);
}

int	create_fork_list(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosophers)
	{
		main->fork_list[i] = create_fork(i);
		i++;
	}
	main->fork_list[i] = NULL;
	if (i != main->number_of_philosophers)
		return (1);
	return (0);
}

int	init_philo(t_main *main, int argc, char **argv)
{
	main->number_of_philosophers = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	main->number_of_times_each_philosophers_must_eat = -1;
	main->time = 0;
	main->tmp = -1;
	main->philo_list = malloc(main->number_of_philosophers * sizeof(t_philo *));
	main->fork_list = malloc(main->number_of_philosophers * sizeof(t_fork *));
	if (!main->fork_list || !main->philo_list || create_philo_list(main)
		|| create_fork_list(main))
	{
		error_management(e_init_failure, main);
		return (1);
	}
	if (argc < 5)
		main->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
	return (0);
}
