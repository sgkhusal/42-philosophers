/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:50:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/05 19:08:46 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		//if (mutex is locked)
			// wait until the mutex is unlocked
		// lock the mutex
		pthread_mutex_lock(&mutex); // faz as 3 coisas acima
		mails++;
		i++;
		// unlock the mutex
		pthread_mutex_unlock(&mutex);
	}
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	pthread_t	thread4;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&thread1, NULL, &routine, NULL))
		return (1);
	if (pthread_create(&thread2, NULL, &routine, NULL))
		return (2);
	if (pthread_create(&thread3, NULL, &routine, NULL))
		return (3);
	if (pthread_create(&thread4, NULL, &routine, NULL))
		return (4);
	if (pthread_join(thread1, NULL))
		return (5);
	if (pthread_join(thread2, NULL))
		return (6);
	if (pthread_join(thread3, NULL))
		return (7);
	if (pthread_join(thread4, NULL))
		return (8);
	pthread_mutex_destroy(&mutex);
	printf("Number of emails: %d\n", mails);
	return (0);
}
