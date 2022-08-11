/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/11 01:28:56 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(long long time, int philo, char *action,
			pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf("%-5lld %i %s\n", time, philo, action);
	pthread_mutex_unlock(print);
}

static void	philo_takes_forks(int nbr, long long starting_time, t_args *philo)
{
	long long	time;

	pthread_mutex_lock(&(philo->right_fork->lock));
	pthread_mutex_lock(&(philo->left_fork->lock));
	philo->right_fork->available = NO;
	philo->left_fork->available = NO;
	time = time_now() - starting_time;
	print_action(time, nbr, "has taken a fork", &(philo->data->lock_print));
	time = time_now() - starting_time;
	print_action(time, nbr, "has taken a fork", &(philo->data->lock_print));
}

void	set_simulation(t_args *philo)
{
	//pthread_mutex_lock(&(philo->data->lock_data));
	philo->data->simulation--;
	//pthread_mutex_unlock(&(philo->data->lock_data));
}

void	update_must_eat(t_args *philo)
{
	if (philo->must_eat > 0)
	{
		philo->must_eat--;
		if (philo->must_eat == NO)
			set_simulation(philo);
	}
}

void	philo_eats(int nbr, int time_eating, t_args *philo)
{
	long long	delta_time;
	long long	eating_start;

	if (simulation(philo) == STOP)
		return ;
	philo_takes_forks(nbr, philo->data->starting_time, philo);
	eating_start = time_now();
	delta_time = eating_start - philo->data->starting_time;
	/* if (simulation(philo) == STOP) // será que precisa disso aqui??
	{
		pthread_mutex_unlock(&(philo->right_fork->lock));
		pthread_mutex_unlock(&(philo->left_fork->lock));
		return ;
	} */
	print_action(delta_time, nbr, "is eating", &(philo->data->lock_print));
	time_wait(time_eating, eating_start);
	philo->right_fork->available = YES;
	philo->left_fork->available = YES;
	pthread_mutex_unlock(&(philo->right_fork->lock));
	pthread_mutex_unlock(&(philo->left_fork->lock));
	update_must_eat(philo);
	philo->last_eat = delta_time + time_eating; // conta o final ou o início? para mim tem que ser o final...
}

void	philo_sleeps(int philo, int time_spleeping, long long starting_time,
			pthread_mutex_t *print)
{
	long long	delta_time;
	long long	sleeping_start;

	sleeping_start = time_now();
	delta_time = sleeping_start - starting_time;
	print_action(delta_time, philo, "is sleeping", print);
	time_wait(time_spleeping, sleeping_start);
}

void	philo_thinks(int philo, long long starting_time, pthread_mutex_t *print)
{
	long long		delta_time;

	delta_time = get_delta_time(starting_time);
	print_action(delta_time, philo, "is thinking", print);
	usleep(1000); // ver se isso impacta em casos com delta t muito pequeno
	//equivale a 1 milisegundo
}
