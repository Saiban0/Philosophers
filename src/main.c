/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:50:01 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/03 16:55:08 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	philosopher_routine(t_main *main, t_philo *philo)
// {
	// 
// }

t_philo	create_philo(t_main *main, int id)
{
	t_philo	new;

	new = malloc(sizeof(philo));
	new->id = id;
	new->alive = 1;
}

int	create_philo_list(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ < main->number_of_philosophers)
		philo[i] = create_philo(main, i);
	philo[i] = NULL;
	if (i != main->number_of_philosophers)
		return (1);
	return (0);
}

void	init_philo(t_main *main, char **argv)
{
	main->number_of_philosophers = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	main->number_of_times_each_philosophers_must_eat = -1;
	if (argc < 4)
		main->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_main	*main;
	t_philo	*philo_list;

	main = malloc(sizeof(t_main));
	philo_list = malloc(main->number_of_philosophers * sizeof(philo));
	if (argc < 3)
		return (1);
	init_philo(main, argv);
	
	return (0);
}
