/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:39:56 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 10:55:33 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	*create_one_philo(pthread_t *philo, t_args *args)
{
	struct timeval	init_time;

	gettimeofday(&init_time, NULL);
	args->init_time = init_time;
	if (pthread_create(philo, NULL, &only_one_philo_routine, (void *)args) != 0)
		pthread_error(philo, args->nbr);
	return (philo);
}

pthread_t	*create_philos(int nbr_of_philos, t_args *args)
{
	struct timeval	init_time;
	pthread_t		*philos;
	int				i;

	philos = malloc(sizeof(pthread_t) * nbr_of_philos);
	if (philos == NULL)
		return (malloc_error());
	if (nbr_of_philos == 1)
		return (create_one_philo(philos, args));
	i = 0;
	gettimeofday(&init_time, NULL);
	while (i < nbr_of_philos)
	{
		args[i].init_time = init_time;
		if (pthread_create(&philos[i], NULL, &routine, (void *)&args[i]) != 0)
			return (pthread_error(philos, args[i].nbr));
		i++;
	}
	return (philos);
}

void	join_philos(pthread_t *philos, int nbr_of_philos)
{
	int	i;

	i = 0;
	while (i < nbr_of_philos)
	{
		if (pthread_join(philos[i], NULL) != 0)
			printf("Error join philo %i thread.\n", i + 1);
		i++;
	}
}
