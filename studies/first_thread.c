/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:58:10 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/03 22:22:13 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>

void	*thread_routine(void *arg)
{
	while (1)
	{
		sleep(1);
		printf("Thread here!\n");
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	thread_1;

	printf("First thread\n");
	pthread_create(&thread_1, NULL, &thread_routine, NULL);
	while (1)
	{
		sleep(2);
		printf("Main here!\n");
	}
	return (0);
}
