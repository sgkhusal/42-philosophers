/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:12:15 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/06 13:19:28 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define THREAD_NUM 30

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex); // faz as 3 coisas acima
		mails++;
		i++;
		pthread_mutex_unlock(&mutex);
	}
}


int	main(void)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL))
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started.\n", i);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(threads[i], NULL))
		{
			perror("Failed to join thread");
			return (2);
		}
		printf("Thread %d has finished execution.\n", i);
		i++;
	}
	printf("Total e-mails = %d\n", mails);
}
