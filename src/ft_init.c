/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:40:40 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/11 15:16:36 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_verif_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][0] == '-')
			return (print_error_msg(e_args));
		while (argv[i][j] == '0' && argv)
			j++;
		if (argv[i][j] == '\0')
			return (print_error_msg(e_args));
		if (ft_strlen(argv[i] + j) > 10)
			return (print_error_msg(e_args_overflow));
		while (argv[i][j] >= '0' && argv[i][j] <= '9' && argv[i][j])
			j++;
		if (argv[i][j] != '\0')
			return (print_error_msg(e_args));
	}
	return (0);
}

int	ft_init_main(t_main *main, int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (print_error_msg(e_args));
	if (ft_verif_arg(argc, argv) == 1)
		return (1);
	main->nb_philo = ft_atol(argv[1]);
	main->time_to_die = ft_atol(argv[2]);
	main->time_to_eat = ft_atol(argv[3]);
	main->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		main->max_meals = ft_atol(argv[5]);
	else
		main->max_meals = -1;
	if (main->nb_philo > 2147483647 || main->time_to_die > 2147483647
		|| main->time_to_eat > 2147483647 || main->time_to_sleep > 2147483647
		|| main->max_meals > 2147483647)
		return (print_error_msg(e_args_overflow));
	return (0);
}

static int	ft_start_threads(t_philo **philo, t_main *main)
{
	t_philo	*temp;
	int		i;

	i = 0;
	temp = *philo;
	while (temp != NULL)
	{
		if (pthread_create(&temp->thread_id, NULL, philo_routine,
				(void *)temp) != 0)
		{
			ft_free_thread(philo, &main, i);
			return (print_error_msg(e_pthread));
		}
		usleep(1000);
		temp = temp->philo_right;
		i++;
	}
	return (0);
}

static int	ft_start(t_philo **philo, t_main **main)
{
	t_philo			*temp;
	struct timeval	start_time;
	int				i;

	i = 0;
	if (gettimeofday(&start_time, NULL) == -1)
	{
		ft_free_philo(*philo, *main, 0);
		return (print_error_msg(e_gettime));
	}
	temp = *philo;
	if (pthread_mutex_init(&(*main)->mutex_print, NULL) != 0)
	{
		ft_free_philo(*philo, *main, 0);
		return (print_error_msg(e_mutex));
	}
	(*main)->start_time = start_time;
	while (temp != NULL)
	{
		if (pthread_mutex_init(&temp->update_time, NULL) != 0)
			return (ft_free_time(philo, main, i));
		i++;
		temp = temp->philo_right;
	}
	return (ft_start_threads(philo, *main));
}

int	ft_init_philo(t_main **main, t_philo **philo)
{
	t_philo	*temp;
	t_philo	*temp2;
	int		i;

	i = 0;
	while (++i <= (*main)->nb_philo)
	{
		temp = malloc(sizeof(t_philo) * 1);
		if (!temp)
			return (ft_free_philo(*philo, *main, e_malloc));
		temp->id = i;
		temp->times_eaten = 0;
		temp->main = *main;
		temp->philo_right = *philo;
		if (pthread_mutex_init(&temp->fork, NULL) != 0)
			return (ft_free_philo(*philo, *main, e_mutex));
		if (i > 1)
			temp->fork_right = &(*philo)->fork;
		else
			temp2 = temp;
		*philo = temp;
	}
	if (i > 1)
		temp2->fork_right = &(*philo)->fork;
	return (ft_start(philo, main));
}
