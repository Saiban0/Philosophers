/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:56:36 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/10 19:37:35 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_check(t_philo *philo, t_main *main)
{
	t_philo	*temp;

	temp = philo;
	while (1)
	{
		pthread_mutex_lock(&temp->update_time);
		if (philo_get_time(temp->last_meal) > temp->main->time_to_die)
		{
			pthread_mutex_lock(&philo->main->mutex_print);
			pthread_mutex_lock(&philo->main->mutex_main);
			if (main->running != 0)
				printf("%ldms %d died (skill issue)\n",
					philo_get_time(temp->main->start_time), temp->id);
			main->running = 0;
			pthread_mutex_unlock(&philo->main->mutex_main);
			pthread_mutex_unlock(&philo->main->mutex_print);
			pthread_mutex_unlock(&temp->update_time);
			return (ft_free_end(philo, main));
		}
		pthread_mutex_unlock(&temp->update_time);
		if (temp->philo_right == NULL)
			temp = philo;
		else
			temp = temp->philo_right;
	}
}

int	main(int argc, char **argv)
{
	t_main	*main;
	t_philo	*philo;

	philo = NULL;
	main = malloc(sizeof(t_main) * 1);
	if (!main)
		return (print_error_msg(e_malloc));
	if (ft_init_main(main, argc, argv) != 0)
	{
		free(main);
		return (1);
	}
	main->running = 1;
	if (pthread_mutex_init(&main->mutex_main, NULL) != 0)
	{
		free(main);
		return (print_error_msg(e_mutex));
	}
	if (main->nb_philo == 1)
		return (ft_solo_bolo(main));
	if (ft_init_philo(&main, &philo) == 1)
		return (1);
	return (ft_death_check(philo, main));
}
