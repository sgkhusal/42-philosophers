/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:12:15 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/08 15:12:33 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define THREAD_NUM 8

pthread_mutex_t	mutex_fuel;
int	fuel = 50;
pthread_mutex_t	mutex_water;
int	water = 10;

void	*routine(void *arg)
{
	if (rand() % 2 == 0)
	{
		pthread_mutex_lock(&mutex_fuel);
		//pthread_mutex_lock(&mutex_fuel); // causes deadlock
		sleep(1);
		pthread_mutex_lock(&mutex_water);
	} else // it can cause a deadlock - two or more threads waiting for each other
	{
		pthread_mutex_lock(&mutex_water);
		sleep(1);
		pthread_mutex_lock(&mutex_fuel);
	}
	fuel += 50;
	water = fuel;
	printf("Incremented fuel to: %d set water to %d\n", fuel, water);
	pthread_mutex_unlock(&mutex_fuel);
	pthread_mutex_unlock(&mutex_water);
}

int	main(void)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_mutex_init(&mutex_water, NULL);
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL))
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(threads[i], NULL))
			perror("Failed to join thread");
		i++;
	}
	printf("Fuel: %d\n", fuel);
	printf("Water: %d\n", water);
	pthread_mutex_destroy(&mutex_fuel);
	pthread_mutex_destroy(&mutex_water);
}
