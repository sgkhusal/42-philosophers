/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:39:56 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/16 00:24:48 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	first_philosopher_data(t_philo_data *philosopher_data,
	int number_of_philosophers, int *forks, char *argv[])
{
	philosopher_data[0].time_to_die = ft_atol(argv[2]);
	philosopher_data[0].time_to_eat = ft_atol(argv[3]);
	philosopher_data[0].time_to_sleep = ft_atol(argv[4]);
	if (number_of_philosophers != 1)
		philosopher_data[0].left_fork = &forks[number_of_philosophers - 1];
	else
		philosopher_data[0].left_fork = NULL; // será que precisa??
}

t_philo_data	*init_philosopher_data(int number_of_philosophers,
	int *forks, char *argv[])
{
	t_philo_data	*philosopher_data;
	int	i;

	philosopher_data = malloc(sizeof(t_philo_data) * number_of_philosophers);
	if (philosopher_data == NULL)
		return (NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		philosopher_data[i].number = i + 1;
		philosopher_data[i].right_fork = &forks[i];
		if (i == 0)
			first_philosopher_data(philosopher_data, number_of_philosophers, forks, argv);
		else
		{
			philosopher_data[i].time_to_die = philosopher_data[i - 1].time_to_die;
			philosopher_data[i].time_to_eat = philosopher_data[i - 1].time_to_eat;
			philosopher_data[i].time_to_sleep = philosopher_data[i - 1].time_to_sleep;
			philosopher_data[i].left_fork = &forks[i - 1];
		}
		i++;
	}
	return (philosopher_data);
}

pthread_t	*create_philosophers(int number_of_philosophers, t_philo_data *philosopher_data)
{
	pthread_t	*philosophers;
	int	i;

	philosophers = malloc(sizeof(pthread_t) * number_of_philosophers);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_create(&philosophers[i], NULL, &routine, (void *)&philosopher_data[i]) != 0)
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
