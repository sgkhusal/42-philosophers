/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 10:57:51 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(int philo, int time_eating, t_args *args)
{
	long long		delta_time;
	struct timeval	tv;

	pthread_mutex_lock(&(args->right_fork->mutex));
	pthread_mutex_lock(&(args->left_fork->mutex));
	args->right_fork->status = FORK_NOT_AVAILABLE;
	args->left_fork->status = FORK_NOT_AVAILABLE;
	gettimeofday(&tv, NULL);
	delta_time = get_delta_time(args->init_time);
	printf("%lld %i has taken a fork\n", delta_time, philo);
	delta_time = get_delta_time(args->init_time);
	printf("%lld %i has taken a fork\n", delta_time, philo);
	delta_time = get_delta_time(args->init_time);
	printf("%lld %i is eating\n", delta_time, philo);
	time_wait(time_eating, tv);
	args->right_fork->status = FORK_AVAILABLE;
	args->left_fork->status = FORK_AVAILABLE;
	pthread_mutex_unlock(&(args->right_fork->mutex));
	pthread_mutex_unlock(&(args->left_fork->mutex));
}

void	philo_sleep(int philo, int time_to_spleep, struct timeval init_tv)
{
	long long		delta_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	delta_time = get_delta_time(init_tv);
	printf("%lld %i is sleeping\n", delta_time, philo);
	time_wait(time_to_spleep, tv);
}

void	philo_think(int philo, struct timeval init_tv)
{
	long long		delta_time;

	delta_time = get_delta_time(init_tv);
	printf("%lld %i is thinking\n", delta_time, philo);
	usleep(1000); // ver se isso impacta em casos com delta t muito pequeno
}

void	philo_die(int philo, struct timeval init_tv)
{
	long long		delta_time;

	delta_time = get_delta_time(init_tv);
	printf("%lld %i died\n", delta_time, philo);
}
