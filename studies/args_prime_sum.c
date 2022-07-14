/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_prime_sum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/06 17:12:23 by sguilher         ###   ########.fr       */
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
	int	*sum;

	index = *(int *)arg;
	sum = malloc(sizeof(int));
	*sum = 0;
	for (int i = 0; i < 5; i++)
		*sum += primes[index + i];
	printf("Local sum: %d\n", *sum);
	return (sum);
}

int	main(void)
{
	pthread_t	threads[2];
	int			pos[2];
	int			*partial_sum;
	int			total_sum;
	int			i;

	i = 0;
	while (i < 2)
	{
		pos[i] = i * 5;
		if (pthread_create(&threads[i], NULL, &routine, (void *)&pos[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	total_sum = 0;
	while (i < 2)
	{
		if (pthread_join(threads[i], (void **)&partial_sum))
			perror("Failed to join thread");
		printf("Partial sum: %d\n", *partial_sum);
		i++;
		total_sum += *partial_sum;
		free(partial_sum);
	}
	printf("Global sum: %d\n", total_sum);
	return (0);
}
