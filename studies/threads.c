/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:37:10 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/05 18:34:47 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void	*thread_routine1(void *arg)
{
	printf("Hello from %s - process ID = %d\n", (char *)arg, getpid());
}

void	*thread_routine2(void *arg)
{
	int	*y;

	y = (int *)arg;
	(*y)++;
	sleep(2);
	printf("Hello from thread 3 - process ID = %d - Value of x: %d\n", getpid(), *y);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	int			child_pid;
	int			x;

	if (pthread_create(&thread1, NULL, &thread_routine1, "thread 1"))
		return (1);
	if (pthread_create(&thread2, NULL, &thread_routine1, "thread 2"))
		return (2);
	if (pthread_join(thread1, NULL))
		return (3);
	if (pthread_join(thread2, NULL))
		return (4);
	x = 2;
	if (pthread_create(&thread2, NULL, &thread_routine2, &x))
		return (5);
	if (pthread_join(thread2, NULL))
		return (6);
	sleep(2);
	printf("Hello from process ID = %d - Value of x: %d\n", getpid(), x);
	child_pid = fork();
	if (child_pid == -1)
		return (5);
	if (child_pid == 0)
		x++;
	sleep(2);
	printf("Hello from process ID = %d - Value of x: %d\n", getpid(), x);
	if (child_pid != 0)
		wait(NULL);
	return (0);
}
