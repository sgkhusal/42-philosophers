/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:12:37 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/08 14:54:00 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define THREAD_NUM 2

void	*routine(void *args)
{
	sleep(1);
	printf("Finished execution.\n");
}

int main(void *arg)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
		pthread_detach(threads[i]);
		i++;
	}
	pthread_exit(0);
}

/* int main(void *arg)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
		pthread_detach(threads[i]);
		i++;
	}
} */

/* int main(void *arg)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
		pthread_detach(threads[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(threads[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	return (0);
} */
