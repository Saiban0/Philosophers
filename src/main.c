/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:50:01 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/03 20:35:19 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_a_philo_dead(t_philo **philo_list)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!philo_list[i]->alive)
			return (1);
	}
	return (0);
}

int	has_every_philo_eaten(t_philo **philo, t_main *main)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (philo[i]->times_eaten
			== main->number_of_times_each_philosophers_must_eat)
			i++;
		else
			return (1);
	}
	return (0);
}

void	philosopher_routine(t_main *main, t_philo *philo)
{
	(void)main;
	(void)philo;
}

void	philo_loop(t_main *main, t_philo **philo_list)
{
	int	i;

	i = 0;
	if (main->number_of_times_each_philosophers_must_eat == -1)
	{
		while (!is_a_philo_dead(philo_list))
		{
			i = 0;
			while (philo_list[i])
			{
				if (philo_list[i]->alive)
					philosopher_routine(main, philo_list[i]);
				i++;
			}
			main->time++;
		}
	}
	else
	{
		while (has_every_philo_eaten(philo_list, main))
		{
			i = 0;
			while (philo_list[i])
			{
				if (philo_list[i]->alive)
					philosopher_routine(main, philo_list[i]);
				i++;
			}
			main->time++;
		}
	}
}

t_philo	*create_philo(int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->id = id;
	new->alive = 1;
	new->times_eaten = 0;
	return (new);
}

int	create_philo_list(t_main *main, t_philo **philo_list)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosophers)
	{
		philo_list[i] = create_philo(i);
		i++;
	}
	philo_list[i] = NULL;
	if (i != main->number_of_philosophers)
		return (1);
	return (0);
}

void	init_philo(t_main *main, int argc, char **argv)
{
	main->number_of_philosophers = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	main->number_of_times_each_philosophers_must_eat = -1;
	main->time = 0;
	if (argc < 5)
		main->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_main	*main;
	t_philo	**philo_list;

	main = malloc(sizeof(t_main));
	init_philo(main, argc, argv);
	philo_list = malloc(main->number_of_philosophers * sizeof(t_philo *));
	if (!main || !philo_list)
		return (-1);
	if (argc < 4)
		return (1);
	create_philo_list(main, philo_list);
	philo_loop(main, philo_list);
	return (0);
}
