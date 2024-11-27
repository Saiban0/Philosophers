/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:50:01 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/13 19:14:54 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	main = NULL;
	if (argc != 5 && argc != 6)
		error_management(e_args, NULL);
	main = malloc(sizeof(t_main));
	if (!main)
		return (-1);
	init_philo(main, argc, argv);
	philo_loop(main);
	philo_end(main);
	error_management(e_none, main);
	return (0);
}
