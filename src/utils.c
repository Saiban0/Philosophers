/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:36:39 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/11 15:16:12 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	philo_get_time(struct timeval start_time)
{
	static struct timeval	end_time;
	long					seconds;
	long					micro;

	if (gettimeofday(&end_time, NULL) == -1)
	{
		print_error_msg(e_gettime);
		return (99999999);
	}
	seconds = end_time.tv_sec - start_time.tv_sec;
	micro = end_time.tv_usec - start_time.tv_usec;
	return ((seconds * 1000) + (micro / 1000));
}

int	check_running(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex_main);
	if (philo->main->running == 0)
	{
		pthread_mutex_unlock(&philo->main->mutex_main);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->mutex_main);
	return (0);
}

void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->main->mutex_print);
	pthread_mutex_lock(&philo->main->mutex_main);
	if (philo->main->running == 1)
		printf("%ld %d %s", philo_get_time(philo->main->start_time),
			philo->id, str);
	pthread_mutex_unlock(&philo->main->mutex_main);
	pthread_mutex_unlock(&philo->main->mutex_print);
}
