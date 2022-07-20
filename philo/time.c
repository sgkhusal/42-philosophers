/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:05:58 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/20 15:37:25 by sguilher         ###   ########.fr       */
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

	usleep(time * 0.5 * 1000); // determinar o melhor valor
	delta_time = get_delta_time(tv);
	while (delta_time < time)
	{
		usleep(10);
		delta_time = get_delta_time(tv);
	}
}
