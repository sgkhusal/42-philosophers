/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:12:15 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/05 19:24:40 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#define THREAD_NUM 2

void	*routine(void *args)
{
	pthread_t	thread;

	thread = pthread_self();
	printf("%lu\n", thread);
	printf("%d\n", (pid_t) syscall(SYS_gettid));
}

int	main(void)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL))
			perror("Failed to create thread");
		// nem sempre o valor da thread será um long int
		// não recomendam imprimir o valor
		// aqui é apenas por demonstração
		printf("%lu\n", threads[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(threads[i], NULL))
			perror("Failed to join thread");
		i++;
	}
}
