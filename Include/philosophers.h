/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:52:49 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/12 16:09:12 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "libamoa.h"

typedef struct s_philo
{
	int				id;
	int				alive;
	int				times_eaten;
	int				forks_held;
	int				last_meal;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_main	*main;
}				t_philo;

typedef struct s_fork
{
	int				id;
	bool			available;
	int				used_by;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_main
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosophers_must_eat;
	t_philo			**philo_list;
	t_fork			**fork_list;
	pthread_mutex_t	mutex;
}				t_main;

typedef enum s_error_management
{
	e_none,
	e_init_failure,
	e_philo_died,
	e_args,
}			t_error;

int		init_philo(t_main *main, int argc, char **argv);
void	error_management(int error_code, t_main *main);
int		create_philo_list(t_main *main);
int		is_a_philo_dead(t_main *main);
int		has_every_philo_eaten(t_main *main);
void	philo_loop(t_main *main);
void	philo_end(t_main *main);
void	error_management(int error_code, t_main *main);
void	philo_eat(t_main *main, t_philo *philo);
void	put_back_forks(t_main *main, t_philo *philo);
void	philo_think(t_main *main, t_philo *philo);
void	philo_sleep(t_main *main, t_philo *philo);
void	time_message(t_philo *philo, char type);

#endif