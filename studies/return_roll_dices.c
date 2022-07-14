/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_roll_dices.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:33 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/06 15:08:26 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 2

void	*roll_dice(void *arg)
{
	int	value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	return ((void *) result);
}

int	main(int argc, char *argv[])
{
	long	dices;
	long	i;
	int		*res;

	if (argc == 1 || argc > 2)
	{
		printf("Run './roll_dices [number of dices]'\n");
		return (1);
	}
	dices = atol(argv[1]);
	pthread_t	threads[dices];
	srand(time(NULL));
	i = 0;
	while (i < dices)
	{
		if (pthread_create(&threads[i], NULL, &roll_dice, NULL) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < dices)
	{
		if (pthread_join(threads[i], (void *)&res))
			perror("Failed to join thread");
		printf("Dice %ld result: %d\n", i + 1, *res);
		free(res);
		i++;
	}
	return (0);
}
