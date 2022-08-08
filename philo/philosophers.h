/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:20:44 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 16:02:27 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset - ainda não usando ///////////////
# include <pthread.h> // threads
# include <sys/time.h> // gettimeofday

// simulation status
# define STOP 0
# define CONTINUE 1

// error numbers
# define E_INVAL 22
# define E_MALLOC 12

# define INT_MAX 2147483647

# define NO 0
# define YES 1
# define OK 0
# define FAILED 1
# define VALID 1
# define NOT_VALID 0

// colors
//# define GREEN "\033[0;32m"
# define RED "\033[38;2;222;56;43m"
# define BLUE "\033[38;2;34;183;235m"
//# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

typedef struct s_time
{
	int	to_die;
	int	eating;
	int	sleeping;
}				t_time;

typedef struct s_input
{
	int			nbr_of_philos;
	long int	nbr_of_times_must_eat;
	t_time		time;
}				t_input;

typedef struct s_fork
{
	int				available;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_args
{
	int				nbr;
	int				total_philos;
	t_time			time;
	int				must_eat;
	int				*died; // se morreu
	int				*simulation;
	int				**order;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned long	last_time_eating; //
	unsigned long	next_time_eating;
	pthread_mutex_t	*print;
	struct timeval	init_time;
}				t_args;

// check input
int			handle_input(int argc, char *argv[], t_input *input);

// threads
int			**create_matrix_order(int nbr_of_philos);
t_fork		*create_forks(int nbr_of_forks);
t_args		*create_args(t_input input, t_fork *forks, int **order, pthread_mutex_t *print);
pthread_t	*create_philos(int nbr_of_philos, t_args *args);
void		*routine(void *arg);
void		*only_one_philo_routine(void *philo_args);
void		join_philos(pthread_t *philos, int nbr_of_philos);

// philosopher's actions
void		philo_eats(int philo, int time_eating, t_args *args);
void		philo_sleeps(int philo, int time_to_spleep, struct timeval init_tv, pthread_mutex_t *print);
void		philo_thinks(int philo, struct timeval init_tv, pthread_mutex_t *print);
void		philo_dies(int philo, struct timeval init_tv, pthread_mutex_t *print);

// time
long long	get_delta_time(struct timeval init_tv);
void		time_wait(int time, struct timeval tv);

// utils
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr); //
void		*malloc_error(void);
void		*pthread_error(pthread_t *philos, int philo_nbr);
void		print_action(long long time, int philo, char *action,
				pthread_mutex_t *print);

#endif
