/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:38:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/26 18:38:57 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*only_one_philo(t_fork *right_fork, int time_to_die, struct timeval init_tv)
{
	double	delta_time;

	pthread_mutex_lock(&(right_fork->mutex));
	right_fork->status = FORK_NOT_AVAILABLE;
	delta_time = get_delta_time(init_tv);
	printf("%f 1 has taken a fork\n", delta_time);
	time_wait(time_to_die, init_tv);
	philo_die(1, init_tv);
	pthread_mutex_unlock(&(right_fork->mutex));
	return ("died");
}

// TODO: lidar com os deltas ts == 0!!
void	*routine(void *philo_args)
{
	t_args	*args;
	int		philo_alive;

	args = (t_args *)philo_args;
	if (args->left_fork == NULL) // pode passar para uma rotina diferente
		return (only_one_philo(args->right_fork, args->time_to_die, args->init_tv));
	if (args->nbr % 2 == 0)
		usleep(args->time_to_eat * 0.9 * 1000); // verificar um valor bom
	if (args->nbr % 2 == 1 && args->is_last_philo)
		usleep(args->time_to_eat * 1.9 * 1000); // verificar um valor bom
	philo_alive = 10; // alterar
	while (philo_alive && args->nbr_of_times_must_eat) // enquanto não morre
	{
		if (args->right_fork->status == FORK_NOT_AVAILABLE || args->left_fork->status == FORK_NOT_AVAILABLE)
		{
			// checar se o philosofo morre
			// printf("philo %i is waiting\n", args->nbr);
			//usleep(100); // talvez seja útil se todos começarem a morrer
			continue ;
		}
		philo_eat(args->nbr, args->time_to_eat, args);
		args->nbr_of_times_must_eat--;
		if (!args->nbr_of_times_must_eat)
			break ;
		philo_sleep(args->nbr, args->time_to_sleep, args->init_tv);
		philo_think(args->nbr, args->init_tv);
		if (args->is_first_philo)
			usleep(args->time_to_eat * 0.9 * 1000);
		philo_alive--;
	}
	if (!philo_alive)
	{
		philo_die(args->nbr, args->init_tv);
		return ("died");
	}
	return ("bye");
}
