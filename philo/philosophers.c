/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:39:56 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/20 16:25:27 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	first_philo_data(t_philo_data *philo_data,
	int philo_qty, int *forks, char *argv[])
{
	philo_data[0].time_to_die = ft_atol(argv[2]);
	philo_data[0].time_to_eat = ft_atol(argv[3]);
	philo_data[0].time_to_sleep = ft_atol(argv[4]);
	if (philo_qty != 1)
		philo_data[0].left_fork = &forks[philo_qty - 1];
	else
		philo_data[0].left_fork = NULL; // será que precisa??
}

t_philo_data	*init_philosopher_data(int number_of_philosophers,
	int *forks, pthread_mutex_t mutex, char *argv[])
{
	t_philo_data	*philo_data;
	int				i;

	philo_data = malloc(sizeof(t_philo_data) * number_of_philosophers);
	if (philo_data == NULL)
		return (NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		philo_data[i].number = i + 1;
		philo_data[i].mutex = mutex;
		philo_data[i].right_fork = &forks[i];
		if (i == 0)
			first_philo_data(philo_data, number_of_philosophers, forks, argv);
		else
		{
			philo_data[i].time_to_die = philo_data[i - 1].time_to_die;
			philo_data[i].time_to_eat = philo_data[i - 1].time_to_eat;
			philo_data[i].time_to_sleep = philo_data[i - 1].time_to_sleep;
			philo_data[i].left_fork = &forks[i - 1];
		}
		i++;
	}
	return (philo_data);
}

pthread_t	*create_philosophers(int number_of_philosophers,
	t_philo_data *philosopher_data)
{
	struct timeval	init_tv;
	pthread_t		*philosophers;
	int				i;

	philosophers = malloc(sizeof(pthread_t) * number_of_philosophers);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	gettimeofday(&init_tv, NULL);
	while (i < number_of_philosophers)
	{
		philosopher_data[i].init_tv = init_tv;
		if (pthread_create(&philosophers[i], NULL, &routine,
				(void *)&philosopher_data[i]) != 0)
		{
			printf("Error creating philosopher %i thread.\n", i + 1);
			free (philosophers); // tá certo fazer isso?
			philosophers = NULL;
			i = number_of_philosophers;
		}
		i++;
	}
	return (philosophers);
}

void	join_philosophers(pthread_t *philosophers, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_join(philosophers[i], NULL) != 0)
			printf("Error join philosopher %i thread.\n", i + 1);
		i++;
	}
}
