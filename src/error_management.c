/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:04:16 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/09 18:33:59 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error_msg(t_error code)
{
	if (code == e_malloc)
		ft_putstr_fd("Failed to malloc\n", STDERR_FILENO);
	if (code == e_args)
		ft_putstr_fd("The arguments seem to be erronous, please refer to the \
			subject\n", STDERR_FILENO);
	if (code == e_gettime)
		ft_putstr_fd("Failure while using gettime\n", STDERR_FILENO);
	if (code == e_mutex)
		ft_putstr_fd("Failure during creation or manipulation of a mutex\n",
			STDERR_FILENO);
	if (code == e_pthread)
		ft_putstr_fd("Failure during initialization of a thread\n",
			STDERR_FILENO);
	if (code == e_args_overflow)
		ft_putstr_fd("Args should be containable in an int\n", STDERR_FILENO);
	return (1);
}

int	ft_free_philo(t_philo *philo, t_main *main, t_error code)
{
	t_philo	*temp;

	temp = philo;
	while (philo)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->philo_right;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&main->mutex_main);
	free(main);
	if (code > 0)
		return (print_error_msg(code));
	return (0);
}

int	ft_free_time(t_philo **philo, t_main **main, int i)
{
	t_philo	*temp;
	int		j;

	j = 0;
	temp = *philo;
	while (temp != NULL && j < i)
	{
		pthread_mutex_destroy(&temp->update_time);
		temp = temp->philo_right;
		j++;
	}
	pthread_mutex_destroy(&(*main)->mutex_print);
	ft_free_philo(*philo, *main, 0);
	return (print_error_msg(e_mutex));
}

int	ft_free_thread(t_main **main, t_philo **philo, int i)
{
	t_philo	*temp;
	int		j;

	j = 0;
	temp = *philo;
	pthread_mutex_lock(&(*main)->mutex_main);
	(*main)->running = -1;
	while (temp != NULL && j < i)
	{
		pthread_join(temp->id, NULL);
		temp = temp->philo_right;
		j++;
	}
	temp = *philo;
	while (temp)
	{
		pthread_mutex_destroy(&temp->update_time);
		temp = temp->philo_right;
	}
	pthread_mutex_destroy(&(*main)->mutex_print);
	return (ft_free_philo(*philo, *main, 0));
}

int	ft_free_end(t_main *main, t_philo *philo)
{
	t_philo	*temp;

	while (temp)
	{
		pthread_join(temp->thread_id, NULL);
		pthread_mutex_destroy(&temp->update_time);
		temp = temp->philo_right;
	}
	temp = philo;
	while (temp)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->philo_right;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&main->mutex_print);
	pthread_mutex_destroy(&main->mutex_main);
	free(main);
	return (0);
}
