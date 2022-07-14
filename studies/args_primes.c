/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_primes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/06 15:08:24 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg)
{
	int	index;

	sleep(1);
	index = *(int *)arg;
	printf("%d ", primes[index]);
}

int	main(void)
{
	pthread_t	threads[10];
	int			pos[10];
	int			i;

	i = 0;
	while (i < 10)
	{
		pos[i] = i;
		if (pthread_create(&threads[i], NULL, &routine, (void *)&pos[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(threads[i], NULL))
			perror("Failed to join thread");
		i++;
	}
	printf("\n");
	return (0);
}
