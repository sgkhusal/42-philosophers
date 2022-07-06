/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_with_thread_not_safe.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:07:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/03 23:42:21 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#define BIG 1000000000UL
uint32_t g_counter = 0;

void	*count_to_big(void *arg)
{
	for (uint32_t i = 0; i < BIG; i++)
		g_counter++;
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &count_to_big, NULL);
	count_to_big(NULL);
	pthread_join(thread, NULL);
	printf("Done. Counter = %u\n", g_counter);
}

// time ./count_with_thread_not_safe
// Done. Counter = 1255435565 ---> WRONG!!! --> a different answer each time
// result = 7.251s --------------> SLOWER!!

// i++ do 3 things:
// read i; --> 2 threads read the same value
// compute i + 1;
// store new value;

// this code is not thread safe!
