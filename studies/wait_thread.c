/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:58:10 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/03 22:35:04 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>

void	*thread_routine(void *arg)
{
	for (int i = 0; i < 10; i++)
	{
		sleep(1);
		printf("Thread here! %i\n", i);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	thread_1;

	pthread_create(&thread_1, NULL, &thread_routine, NULL);
	for (int i = 0; i < 3; i++)
	{
		sleep(2);
		printf("Main here! %i\n", i);
	}
	printf("Wainting the thread to finish\n");
	pthread_join(thread_1, NULL); // execute without to see the behavior
	printf("The thread finished\n");
	return (0);
}
