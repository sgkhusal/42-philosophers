/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:33:58 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/16 01:00:24 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	struct	timeval	tv1;
	struct	timeval	tv2;
	double	delta_time;

	gettimeofday(&tv1, NULL);
	printf("time = %lis %li microsec\n", tv1.tv_sec, tv1.tv_usec);
	usleep(1000000);
	gettimeofday(&tv2, NULL);
	printf("time = %lis %li microsec\n", tv2.tv_sec, tv2.tv_usec);
	printf("delta time = %lis %li microsec\n", tv2.tv_sec - tv1.tv_sec, tv2.tv_usec - tv1.tv_usec);
	delta_time = (tv2.tv_sec - tv1.tv_sec) * 1000 + (double)(tv2.tv_usec - tv1.tv_usec) / 1000;
	printf("delta time = %f milliseconds\n", delta_time);
	return (0);
}
