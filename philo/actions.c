/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/16 02:33:21 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

double	get_delta_time(struct timeval init_tv)
{
	struct timeval	tv;
	double			delta_time;

	gettimeofday(&tv, NULL);
	delta_time = (tv.tv_sec - init_tv.tv_sec) * 1000;
	delta_time += (double)(tv.tv_usec - init_tv.tv_usec) / 1000;
	return (delta_time);
}

void	time_wait(int time, struct timeval tv)
{
	double	delta_time;

	usleep(time * 900);
	while (delta_time < time)
	{
		usleep(100);
		delta_time = get_delta_time(tv);
	}
}

void	philo_eat(int philosopher, int time_to_eat, struct timeval init_tv)
{
	double			delta_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	delta_time = get_delta_time(init_tv);
	printf("%f %i has taken a fork\n", delta_time, philosopher);
	delta_time = get_delta_time(init_tv);
	printf("%f %i has taken a fork\n", delta_time, philosopher);
	delta_time = get_delta_time(init_tv);
	printf("%f %i is eating\n", delta_time, philosopher);
	time_wait(time_to_eat, tv);
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
}

void	philo_die(int philosopher, struct timeval init_tv)
{
	double			delta_time;

	delta_time = get_delta_time(init_tv);
	printf("%f %i died\n", delta_time, philosopher);
}

void	*routine(void *arg)
{
	t_philo_data	*philosopher_data;

	philosopher_data = (t_philo_data *)arg;
	printf("Hello from philosopher %i\n", philosopher_data->number);
	philo_eat(philosopher_data->number, philosopher_data->time_to_eat, philosopher_data->init_tv);
	philo_sleep(philosopher_data->number, philosopher_data->time_to_sleep, philosopher_data->init_tv);
	philo_think(philosopher_data->number, philosopher_data->init_tv);
	philo_die(philosopher_data->number, philosopher_data->init_tv);
	return ("tchau");
}
