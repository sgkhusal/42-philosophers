/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:42:53 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 16:18:30 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_philo_forks(t_args *args, t_fork *forks, int index,
	int nbr_of_philos)
{
	args->right_fork = &forks[index];
	if (nbr_of_philos == 1)
		args->left_fork = NULL;
	else if (index == 0)
		args->left_fork = &forks[nbr_of_philos - 1];
	else
		args->left_fork = &forks[index - 1];
}

t_args	*create_args(t_input input, t_fork *forks, int **order, pthread_mutex_t *print)
{
	t_args	*args;
	int		i;
	int		*simulation;

	simulation = malloc(sizeof(int));

	args = malloc(sizeof(t_args) * input.nbr_of_philos);
	if (args == NULL)
		return (malloc_error());
	i = 0;
	*simulation = input.nbr_of_times_must_eat;
	while (i < input.nbr_of_philos)
	{
		args[i].nbr = i + 1;
		args[i].total_philos = input.nbr_of_philos;
		args[i].time = input.time;
		args[i].must_eat = input.nbr_of_times_must_eat;
		set_philo_forks(&args[i], forks, i, input.nbr_of_philos);
		args[i].order = order;
		if (args[i].order[0][i] == 1)
			args[i].next_time_eating = 0;
		else if (args[i].order[0][i] == 0 && args[i].order[1][i] == 1)
			args[i].next_time_eating = input.time.eating;
		else
			args[i].next_time_eating = 2 * input.time.eating;
		args[i].last_time_eating = 0;
		args[i].print = print;
		args[i].simulation = simulation;
		i++;
	}
	return (args);
}