/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solo_bolo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:58:46 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/09 18:32:14 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*solo_bolo_routine(void *temp)
{
	t_philo *philo;

	philo = (t_philo *)temp;
	pthread_mutex_lock(&philo->fork);
	printf("0ms 1 has taken a left fork\n");
	usleep(philo->main->time_to_die);
	printf("%dms 1 died (skill issue)\n", philo->main->time_to_die);
	pthread_mutex_unlock(&philo->fork);
	return (NULL);
}


int	ft_solo_bolo(t_main *main)
{
	t_philo	*temp;

	temp = malloc(sizeof(t_philo));
	if (!temp)
	{
		free(main);
		return (print_error_msg(e_malloc));
	}
	temp->main = main;
	if (pthread_mutex_init(&temp->fork, NULL) == 0)
	{
		if (pthread_create(&temp->thread_id, NULL, solo_bolo_routine,
				(void *)temp) == 0)
			pthread_join(temp->thread_id, NULL);
	}
	else
		print_error_msg(e_mutex);
	pthread_mutex_destroy(&main->mutex_main);
	free(main);
	free(temp);
	return (0);
}
