/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/20 16:27:55 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(int philosopher, int time_to_eat, t_philo_data *data)
{
	double			delta_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	delta_time = get_delta_time(data->init_tv);
	printf("%f %i has taken a fork\n", delta_time, philosopher);
	delta_time = get_delta_time(data->init_tv);
	printf("%f %i has taken a fork\n", delta_time, philosopher);
	delta_time = get_delta_time(data->init_tv);
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

void	*routine(void *args)
{
	t_philo_data	*data;

	data = (t_philo_data *)args;
	printf("Hello from philosopher %i\n", data->number);
	while (1) // enquanto não morre
	{
		philo_eat(data->number, data->time_to_eat, data);
		philo_sleep(data->number, data->time_to_sleep, data->init_tv);
		philo_think(data->number, data->init_tv);
	}
	philo_die(data->number, data->init_tv);
	return ("tchau");
}
