/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:02:28 by rivasque          #+#    #+#             */
/*   Updated: 2024/05/06 12:11:47 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

// COLORS (for text	\x1B[38;2;R;G;Bm)
# define RED 	"\x1b[31m"
# define ORANGE "\x1B[38;2;255;128;0m"
# define PINK 	"\x1B[38;2;255;151;203m"
# define PURPLE "\033[0;35m"
# define YELLOW	"\x1b[33m"
# define CLEAR 	"\033[0m"

// TAKS
typedef enum e_tasks
{
	SLEEP,
	THINK,
	TAKE_FORK,
	EAT,
	DEAD
}	t_tasks;

typedef struct s_data	t_data;

// FORK
typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
}					t_fork;

//EACH PHILOSOPHER
typedef struct s_philo
{
	int				id;
	size_t			time_last_eat;
	int				nbr_meals;
	pthread_mutex_t	philo_mtx;
	bool			dead_flag;
	t_data			*data;
}					t_philo;

//GENERAL STRUCTURE
struct s_data
{
	int				n_philos;
	size_t			start;
	size_t			start_prog;
	bool			end;
	pthread_t		*thrds;
	int				threads_ok;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				max_meals;
	t_philo			*philos;
	pthread_mutex_t	print_msg;
	pthread_mutex_t	data_mtx;
	pthread_t		monitor;
	t_fork			*forks;
};

// CHECK ARGUMENTS & INIT
int		valid_args(char **argv);
int		init_data(t_data *data, char **argv);
int		ft_atoi(char *str);

// ACTIONS
void	print_message(t_philo *philo, int task);
void	philo_sleeping(t_philo *philo);
int		philo_eating(t_philo *philo, int fork_1, int fork_2);
bool	philo_dead(t_philo *philo);
int		philo_full(t_philo *philo);
int		all_full(int meals, t_data *data);

// UTILS
size_t	time_at_moment(void);
void	ft_usleep(size_t millesecons);
bool	check_dead(t_data *data, int i);
int		philo_full(t_philo *philo);
bool	end_program(t_philo *philo);

//ROUTINE
void	*routine_monitor(void *args);
void	*rt(void *data);
void	*routine(void *data);

//THREADS
int		init_threads(t_data *data);
void	join_threads(t_data *data);

//DESTROY MTX & FREE
void	destroy_and_free(t_data *data);
void	destroy_mtx(t_data *data);
void	destroy_and_free_all(t_data *data);

#endif