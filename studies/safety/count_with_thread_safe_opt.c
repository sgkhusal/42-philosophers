/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_with_thread_safe_opt.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:07:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/08 18:43:08 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#define BIG 1000000000UL
uint32_t g_counter = 0;
pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

void	*count_to_big(void *arg)
{
	uint32_t	local;

	local = 0;
	for (uint32_t i = 0; i < BIG; i++)
		local++;
	pthread_mutex_lock(&lock);
	g_counter += local;
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;
	char		*buf;
	int			buflen;

	pthread_create(&thread, NULL, &count_to_big, NULL);
	count_to_big(NULL);
	pthread_join(thread, NULL);
	printf("Done. Counter = %u\n", g_counter);
}

// time ./count_with_thread_safe
// Done. Counter = 2000000000 ---> correct!
// result = 3m40.687s -----------> TO MUCH SLOWER!!

// this code is thread safe!
