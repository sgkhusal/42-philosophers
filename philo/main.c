/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/16 01:48:01 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	pthread_t		*philosophers;
	t_philo_data	*philosopher_data;
	int				number_of_philosophers;
	int				*forks;
	struct timeval	init_tv;

	if (handle_input(argc, argv) == FAILED)
		return (E_INVAL);
	gettimeofday(&init_tv, NULL);
	printf("time = %lis %li microsec\n", init_tv.tv_sec, init_tv.tv_usec);
	number_of_philosophers = ft_atol(argv[1]);
	// se número de filósofos = 1: deve morrer - left_fork: problema!!
	forks = create_forks(number_of_philosophers);
	if (forks == NULL)
		return (E_MALLOC);
	philosopher_data = init_philosopher_data(number_of_philosophers,
			forks, argv, init_tv);
	if (philosopher_data == NULL)
		return (E_MALLOC); // must clean
	philosophers = create_philosophers(number_of_philosophers,
			philosopher_data);
	if (philosophers == NULL)
		return (E_MALLOC); // must clean
	join_philosophers(philosophers, number_of_philosophers);
	return (0);
}
