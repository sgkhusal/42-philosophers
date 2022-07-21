/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:39:56 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/20 23:51:35 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	fill_first_philo_args(t_philo_args *philo_args, int philo_qty,
	t_fork *forks, char *argv[])
{
	philo_args[0].number = 1;
	philo_args[0].right_fork = &forks[0];
	philo_args[0].time_to_die = ft_atol(argv[2]);
	philo_args[0].time_to_eat = ft_atol(argv[3]);
	philo_args[0].time_to_sleep = ft_atol(argv[4]);
	philo_args[0].is_first_philosopher = YES;
	philo_args[0].is_last_philosopher = NO;
	if (philo_qty == 1)
		philo_args[0].left_fork = NULL; // será que precisa??
	else
		philo_args[0].left_fork = &forks[philo_qty - 1];
}

static void	fill_philo_args(t_philo_args *philo_args,
	int number_of_philosophers, t_fork *forks)
{
	int	i;

	i = 1;
	while (i < number_of_philosophers)
	{
		philo_args[i].number = i + 1;
		philo_args[i].right_fork = &forks[i];
		philo_args[i].left_fork = &forks[i - 1];
		philo_args[i].time_to_die = philo_args[0].time_to_die;
		philo_args[i].time_to_eat = philo_args[0].time_to_eat;
		philo_args[i].time_to_sleep = philo_args[0].time_to_sleep;
		philo_args[i].number_of_times_must_eat = philo_args[0].number_of_times_must_eat;
		philo_args[i].is_first_philosopher = NO;
		if (i + 1 == number_of_philosophers)
			philo_args[i].is_last_philosopher = YES;
		else
			philo_args[i].is_last_philosopher = NO;
		i++;
	}
}

t_philo_args	*create_philosophers_args(int number_of_philosophers,
	t_fork *forks, char *argv[], int argc)
{
	t_philo_args	*philo_args;

	philo_args = malloc(sizeof(t_philo_args) * number_of_philosophers);
	if (philo_args == NULL)
		return (NULL);
	fill_first_philo_args(philo_args, number_of_philosophers, forks, argv);
	if (argc == 6)
		philo_args[0].number_of_times_must_eat = ft_atol(argv[5]);
	else
		philo_args[0].number_of_times_must_eat = -1;
	if (number_of_philosophers > 1)
		fill_philo_args(philo_args, number_of_philosophers, forks);
	return (philo_args);
}

pthread_t	*create_philosophers(int number_of_philosophers,
	t_philo_args *philosopher_args)
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
		philosopher_args[i].init_tv = init_tv;
		if (pthread_create(&philosophers[i], NULL, &routine,
				(void *)&philosopher_args[i]) != 0)
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
