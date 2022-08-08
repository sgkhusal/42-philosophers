/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 16:16:43 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(int nbr, int time_eating, t_args *philo)
{
	long long		delta_time;
	struct timeval	time;

	pthread_mutex_lock(&(philo->right_fork->mutex));
	pthread_mutex_lock(&(philo->left_fork->mutex));
	philo->right_fork->available = NO;
	philo->left_fork->available = NO;
	gettimeofday(&time, NULL);
	delta_time = get_delta_time(philo->init_time);
	print_action(delta_time, nbr, "has taken a fork", philo->print);
	delta_time = get_delta_time(philo->init_time);
	print_action(delta_time, nbr, "has taken a fork", philo->print);
	delta_time = get_delta_time(philo->init_time);
	print_action(delta_time, nbr, "is eating", philo->print);
	if (philo->must_eat > 0) //
		philo->must_eat--;
	time_wait(time_eating, time);
	philo->right_fork->available = YES;
	philo->left_fork->available = YES;
	pthread_mutex_unlock(&(philo->right_fork->mutex));
	pthread_mutex_unlock(&(philo->left_fork->mutex));
	philo->last_time_eating = delta_time + time_eating;
}

void	philo_sleeps(int philo, int time_to_spleep, struct timeval init_time, pthread_mutex_t *print)
{
	long long		delta_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	delta_time = get_delta_time(init_time);
	print_action(delta_time, philo, "is sleeping", print);
	time_wait(time_to_spleep, time);
}

void	philo_thinks(int philo, struct timeval init_time, pthread_mutex_t *print)
{
	long long		delta_time;

	delta_time = get_delta_time(init_time);
	print_action(delta_time, philo, "is thinking", print);
	usleep(1000); // ver se isso impacta em casos com delta t muito pequeno
}

void	philo_dies(int philo, struct timeval init_time, pthread_mutex_t *print)
{
	long long		delta_time;

	delta_time = get_delta_time(init_time);
	print_action(delta_time, philo, "died", print);
}
