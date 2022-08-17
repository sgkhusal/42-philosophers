/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:01:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/17 21:14:39 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*create_forks(int number_of_forks)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * number_of_forks);
	if (forks == NULL)
		return (malloc_error());
	while (i < number_of_forks)
	{
		forks[i].available = YES;
		pthread_mutex_init(&(forks[i].lock), NULL);
		pthread_mutex_init(&(forks[i].lock_value), NULL);
		i++;
	}
	return (forks);
}

int	has_fork(t_fork *fork)
{
	int	available;

	pthread_mutex_lock(&(fork->lock_value));
	available = fork->available;
	pthread_mutex_unlock(&(fork->lock_value));
	return (available);
}

static void	update_fork_value(t_fork *fork, int value)
{
	pthread_mutex_lock(&(fork->lock_value));
	fork->available = value;
	pthread_mutex_unlock(&(fork->lock_value));
}

void	philo_takes_forks(int nbr, long long starting_time, t_args *philo)
{
	long long	time;

	pthread_mutex_lock(&(philo->left_fork->lock));
	pthread_mutex_lock(&(philo->right_fork->lock));
	update_fork_value(philo->left_fork, NO);
	update_fork_value(philo->right_fork, NO);
	time = time_now() - starting_time;
	print_action(time, nbr, "has taken a fork", philo->data);
	time = time_now() - starting_time;
	print_action(time, nbr, "has taken a fork", philo->data);
}

void	philo_drops_forks(t_args *philo)
{
	pthread_mutex_unlock(&(philo->left_fork->lock));
	pthread_mutex_unlock(&(philo->right_fork->lock));
	update_fork_value(philo->left_fork, YES);
	update_fork_value(philo->right_fork, YES);
}
