/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:42:53 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 10:47:04 by sguilher         ###   ########.fr       */
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

t_args	*create_args(t_input input, t_fork *forks, int **order)
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
		args[i].input = input;
		args[i].order = order;
		args[i].is_first_philo = NO;
		if (i == 0)
			args[i].is_first_philo = YES;
		args[i].is_last_philo = NO;
		if (i + 1 == input.nbr_of_philos)
			args[i].is_last_philo = YES;
		set_philo_forks(&args[i], forks, i, input.nbr_of_philos);
		i++;
	}
	return (args);
}