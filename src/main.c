/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:50:01 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/06 15:27:44 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (-1);
	if (argc < 4)
		return (1);
	init_philo(main, argc, argv);
	philo_loop(main);
	philo_end(main);
	return (0);
}
