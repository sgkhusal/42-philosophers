/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/21 00:57:51 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(int philosopher, int time_to_eat, t_philo_args *args)
{
	double			delta_time;
	struct timeval	tv;

	pthread_mutex_lock(&(args->right_fork->mutex));
	pthread_mutex_lock(&(args->left_fork->mutex));
	args->right_fork->status = FORK_NOT_AVAILABLE;
	args->left_fork->status = FORK_NOT_AVAILABLE;
	gettimeofday(&tv, NULL);
	delta_time = get_delta_time(args->init_tv);
	printf("%f %i has taken a fork\n", delta_time, philosopher);
	delta_time = get_delta_time(args->init_tv);
	printf("%f %i has taken a fork\n", delta_time, philosopher);
	delta_time = get_delta_time(args->init_tv);
	printf("%f %i is eating\n", delta_time, philosopher);
	time_wait(time_to_eat, tv);
	args->right_fork->status = FORK_AVAILABLE;
	args->left_fork->status = FORK_AVAILABLE;
	pthread_mutex_unlock(&(args->right_fork->mutex));
	pthread_mutex_unlock(&(args->left_fork->mutex));
}

void	philo_sleep(int philosopher, int time_to_spleep, struct timeval init_tv)
{
	double			delta_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	delta_time = get_delta_time(init_tv);
	printf("%f %i is sleeping\n", delta_time, philosopher);
	time_wait(time_to_spleep, tv);
}

void	philo_think(int philosopher, struct timeval init_tv)
{
	double			delta_time;

	delta_time = get_delta_time(init_tv);
	printf("%f %i is thinking\n", delta_time, philosopher);
	usleep(1000); // ver se isso impacta em casos com delta t muito pequeno
}

void	philo_die(int philosopher, struct timeval init_tv)
{
	double			delta_time;

	delta_time = get_delta_time(init_tv);
	printf("%f %i died\n", delta_time, philosopher);
}

void	*only_one_philo(t_fork *right_fork, int time_to_die, struct timeval init_tv)
{
	double			delta_time;

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
void	*routine(void *args)
{
	t_philo_args	*philo_args;
	int				philo_alive;

	philo_args = (t_philo_args *)args;
	if (philo_args->left_fork == NULL) // pode passar para uma rotina diferente
		return (only_one_philo(philo_args->right_fork, philo_args->time_to_die, philo_args->init_tv));
	if (philo_args->number % 2 == 0)
		usleep(philo_args->time_to_eat * 0.9 * 1000); // verificar um valor bom
	if (philo_args->number % 2 == 1 && philo_args->is_last_philosopher)
		usleep(philo_args->time_to_eat * 1.9 * 1000); // verificar um valor bom
	philo_alive = 10; // alterar
	while (philo_alive && philo_args->number_of_times_must_eat) // enquanto não morre
	{
		if (philo_args->right_fork->status == FORK_NOT_AVAILABLE || philo_args->left_fork->status == FORK_NOT_AVAILABLE)
		{
			// checar se o philosofo morre
			// printf("Philosopher %i is waiting\n", philo_args->number);
			//usleep(100); // talvez seja útil se todos começarem a morrer
			continue ;
		}
		philo_eat(philo_args->number, philo_args->time_to_eat, philo_args);
		philo_args->number_of_times_must_eat--;
		if (!philo_args->number_of_times_must_eat)
			break ;
		philo_sleep(philo_args->number, philo_args->time_to_sleep, philo_args->init_tv);
		philo_think(philo_args->number, philo_args->init_tv);
		if (philo_args->is_first_philosopher)
			usleep(philo_args->time_to_eat * 0.9 * 1000);
		philo_alive--;
	}
	if (!philo_alive)
	{
		philo_die(philo_args->number, philo_args->init_tv);
		return ("died");
	}
	return ("bye");
}
