/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:40:50 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/09 18:53:42 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_LEFTFORKMSG "has taken a left hand fork\n"
# define PHILO_RIGHTFORKMSG "has taken a left hand fork\n"
# define PHILO_EATMSG "is eating\n"
# define PHILO_SLEEPMSG "is sleeping\n"
# define PHILO_THINKMSG "is thinking\n"


typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	struct timeval	start_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_main;
	int				running;
}				t_main;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	struct timeval	last_meal;
	t_main			*main;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	update_time;
	pthread_t		thread_id;
	struct s_philo	*philo_right;
}				t_philo;

typedef enum s_error_codes
{
	e_none = 0,
	e_malloc = 1,
	e_args = 2,
	e_gettime = 3,
	e_mutex = 4,
	e_pthread = 5,
	e_args_overflow = 6,
}			t_error;

/*			Error_management			*/
int		print_error_msg(t_error code);
int		ft_free_philo(t_philo *philo, t_main *main, t_error code);
int		ft_free_thread(t_main **main, t_philo **philo, int i);
int		ft_free_time(t_philo **philo, t_main **main, int i);
int		ft_error_get_time(t_philo *philo);
int		ft_free_end(t_main *main, t_philo *philo);

/*			Initialization			*/
int		ft_init_main(t_main *main, int argc, char **argv);
int		ft_init_philo(t_main **main, t_philo **philo);

/*			Routine			*/
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
void	*philo_routine(void *temp);

/*			Utilities			*/
void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);
long	ft_atol(const char *str);
long	philo_get_time(struct timeval start_time);
void	philo_print(t_philo *philo, char *msg);
int		check_running(t_philo *philo);

int		ft_solo_bolo(t_main *main);

#endif