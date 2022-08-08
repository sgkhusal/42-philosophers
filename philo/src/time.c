/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:05:58 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/27 23:38:31 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_delta_time(struct timeval init_tv)
{
	struct timeval	tv;
	//long long		delta_time;
	long long previous;
	long long now;

	previous = (init_tv.tv_sec * 1000) + (init_tv.tv_usec / 1000);
	gettimeofday(&tv, NULL);
	/* delta_time = (tv.tv_sec - init_tv.tv_sec) * 1000;
	delta_time += (tv.tv_usec - init_tv.tv_usec) / 1000;
	return (delta_time); */
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (now - previous);
}

void	time_wait(int time, struct timeval tv)
{
	long long int	delta_time;

	usleep(time * 0.9 * 1000); // determinar o melhor valor
	delta_time = get_delta_time(tv);
	while (delta_time < time)
	{
		usleep(100);
		delta_time = get_delta_time(tv);
	}
}
