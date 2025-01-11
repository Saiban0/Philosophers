/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:40:50 by bchedru           #+#    #+#             */
/*   Updated: 2025/01/11 15:15:03 by bchedru          ###   ########.fr       */
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
# define PHILO_RIGHTFORKMSG "has taken a right hand fork\n"
# define PHILO_EATMSG "is eating\n"
# define PHILO_SLEEPMSG "is sleeping\n"
# define PHILO_THINKMSG "is thinking\n"

typedef struct s_main
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	struct timeval	start_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_main;
	int				running;
}					t_main;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	struct timeval	last_meal;
	struct s_main	*main;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	update_time;
	pthread_t		thread_id;
	struct s_philo	*philo_right;
}					t_philo;

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
int		ft_free_time(t_philo **philo, t_main **main, int i);
int		ft_error_get_time(t_philo *philo);
int		ft_free_thread(t_philo **philo, t_main **main, int i);
int		ft_free_end(t_philo *philo, t_main *main);

/* ==================== function utils ==================== */

long	ft_atol(const char *nptr);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);

/* ==================== function init arg ==================== */

int		ft_init_main(t_main *main, int argc, char **argv);

/* ==================== function pthread ==================== */

int		ft_solo_bolo(t_main *main);
int		ft_init_philo(t_main **main, t_philo **philo);
void	*philo_routine(void *temp);

/* ==================== function print/time ==================== */

void	philo_print(t_philo *philo, char *str);
int		check_running(t_philo *philo);
long	philo_get_time(struct timeval start_time);

#endif
