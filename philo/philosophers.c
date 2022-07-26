/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:39:56 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/26 18:32:38 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_philo_forks(t_args *args, t_fork *forks, int index,
	int nbr_of_philos)
{
	args->right_fork = &forks[index];
	if (index == 0 && nbr_of_philos == 1)
		args->left_fork = NULL; // será que precisa??
	else if (index == 0)
		args->left_fork = &forks[nbr_of_philos - 1];
	else
		args->left_fork = &forks[index - 1];
}

t_args	*create_args(t_input input, t_fork *forks)
{
	t_args	*args;
	int		i;

	args = malloc(sizeof(t_args) * input.nbr_of_philos);
	if (args == NULL)
		return (malloc_error());
	i = 0;
	while (i < input.nbr_of_philos)
	{
		args[i].nbr = i + 1;
		args[i].time_to_die = input.time_to_die;
		args[i].time_to_eat = input.time_to_eat;
		args[i].time_to_sleep = input.time_to_sleep;
		args[i].nbr_of_times_must_eat = input.nbr_of_times_must_eat;
		args[i].is_first_philo = NO;
		if (i == 0)
			args[i].is_first_philo = YES;
		args[i].is_last_philo = NO;
		if (i + 1 == input.nbr_of_philos && i != 0) // ver se c 1 n pode mudar
			args[i].is_last_philo = YES;
		set_philo_forks(&args[i], forks, i, input.nbr_of_philos);
		i++;
	}
	return (args);
}

pthread_t	*create_philos(int nbr_of_philos, t_args *args)
{
	struct timeval	init_tv;
	pthread_t		*philos;
	int				i;

	philos = malloc(sizeof(pthread_t) * nbr_of_philos);
	if (philos == NULL)
		return (malloc_error());
	i = 0;
	gettimeofday(&init_tv, NULL);
	//if (nbr_of_philos == 1)
		// return criar a thread para um filósofo com a função específica
	while (i < nbr_of_philos)
	{
		args[i].init_tv = init_tv;
		if (pthread_create(&philos[i], NULL, &routine, (void *)&args[i]) != 0)
		{
			printf("Error creating philo %i thread.\n", i + 1);
			free (philos);// tá certo fazer isso, sem esperar as outras threads?
			return (NULL);
		}
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
