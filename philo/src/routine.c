/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:38:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/12 01:36:29 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*only_one_philo_routine(void *args)
{
	long long	delta_time;
	t_args		*philo;

	philo = (t_args *)args;
	pthread_mutex_lock(&(philo->right_fork->lock));
	philo->right_fork->available = NO;
	delta_time = get_delta_time(philo->data->starting_time);
	print_action(delta_time, philo->nbr, "has taken a fork", philo->data);
	time_wait(philo->data->time.to_die, philo->data->starting_time);
	pthread_mutex_unlock(&(philo->right_fork->lock));
	return (NULL);
}

void	wait_to_eat(t_args *philo, int time_sleeping, int time_eating)
{
	int	must_eat;
	int	index;

	if (time_sleeping > 2 * time_eating + 10)
		return ;
	philo->iteration += 2;
	index = philo->iteration % philo->data->nbr_of_philos;
	must_eat = philo->data->order[index][philo->nbr - 1];
	if (must_eat)
		time_wait2(time_eating * 2, philo->last_eat);
	else
	{
		time_wait2(time_eating * 3, philo->last_eat);
		philo->iteration++;
	}
}

void	*routine(void *args)
{
	t_args	*philo;

	philo = (t_args *)args;
	if (philo->next_eat != 0)
		usleep(philo->next_eat * 0.9 * 1000);
	while (simulation(philo->data) != STOP)
	{
		if (!philo->right_fork->available || !philo->left_fork->available)
		{
			usleep(500);
			continue ;
		}
		philo_eats(philo->nbr, philo->data->time.eating, philo);
		philo_sleeps(philo->nbr, philo->data->time.sleeping,
			philo->data->starting_time, philo->data);
		philo_thinks(philo->nbr, philo->data->starting_time, philo->data);
		wait_to_eat(philo, philo->data->time.sleeping,
			philo->data->time.eating);
	}
	return (NULL);
}

void	philo_dies(int philo, long long starting_time, t_data *data)
{
	long long		delta_time;

	delta_time = get_delta_time(starting_time);
	pthread_mutex_lock(&(data->lock_print));
	printf("%-5lld %i %s\n", delta_time, philo, "died");
	pthread_mutex_unlock(&(data->lock_print));
}
