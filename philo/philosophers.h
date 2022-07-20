/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:20:44 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/20 16:24:16 by sguilher         ###   ########.fr       */
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

// philosophers activities
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

# define OK 0
# define FAILED 1
# define IS_VALID 0
# define IS_NOT_VALID 1

// colors
//# define GREEN "\033[0;32m"
# define RED "\033[38;2;222;56;43m"
# define BLUE "\033[38;2;34;183;235m"
//# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

typedef struct s_data
{
	int	*forks;
	int	number_of_philosophers;
}					t_data;

typedef struct s_philo_data
{
	int				number;
	int				*left_fork;
	int				*right_fork;
	int				is_last_philosopher; // ainda não usando
	int				is_first_philosopher; // ainda não usando
	int				must_eat; // ainda não usando
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_must_eat;
	pthread_mutex_t	mutex;
	struct timeval	init_tv;
}				t_philo_data;

// check input
int				handle_input(int argc, char *argv[]);

int				*create_forks(int number_of_forks);
t_philo_data	*init_philosopher_data(int number_of_philosophers, int *forks,
					pthread_mutex_t mutex, char *argv[]);
pthread_t		*create_philosophers(int number_of_philosophers,
					t_philo_data *philosopher_data);
void			join_philosophers(pthread_t *philosophers,
					int number_of_philosophers);

// actions
void			*routine(void *arg);

// time
double			get_delta_time(struct timeval init_tv);
void			time_wait(int time, struct timeval tv);

// utils
int				ft_isdigit(int c);
long int		ft_atol(const char *nptr);

#endif
