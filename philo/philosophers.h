/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:20:44 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/27 15:09:50 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <pthread.h> // threads
# include <sys/time.h> // gettimeofday

// philosophers status
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 0

# define FORK_AVAILABLE 1
# define FORK_NOT_AVAILABLE 0

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

typedef struct s_input
{
	int	nbr_of_philos;
	int	time_to_die;
	int	time_eating;
	int	time_sleeping;
	int	nbr_of_times_must_eat;
}				t_input;

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_args
{
	int				nbr;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_eating;
	int				time_sleeping;
	int				nbr_of_times_must_eat;
	int				must_eat; // ainda não usando
	int				is_last_philo; // ainda não usando
	int				is_first_philo; // ainda não usando
	int				**order;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct timeval	init_tv;
}				t_args;

// check input
int			handle_input(int argc, char *argv[], t_input *input);

// threads
int			**create_matrix_order(int nbr_of_philos);
t_fork		*create_forks(int nbr_of_forks);
t_args		*create_args(t_input input, t_fork *forks, int **order);
pthread_t	*create_philos(int nbr_of_philos, t_args *args);
void		*routine(void *arg);
void		*only_one_philo_routine(void *philo_args);
void		join_philos(pthread_t *philos, int nbr_of_philos);

// philosopher's actions
void		philo_eat(int philo, int time_eating, t_args *args);
void		philo_sleep(int philo, int time_to_spleep, struct timeval init_tv);
void		philo_think(int philo, struct timeval init_tv);
void		philo_die(int philo, struct timeval init_tv);

// time
double		get_delta_time(struct timeval init_tv);
void		time_wait(int time, struct timeval tv);

// utils
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr); //
void		*malloc_error(void);
void		*pthread_error(pthread_t *philos, int philo_nbr);

#endif
