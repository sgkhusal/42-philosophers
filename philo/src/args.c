/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:42:53 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/11 14:52:53 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_matrix(int **m, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%i ", m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	fill_data(t_data *data)
{
	data->simulation = data->nbr_of_philos;
	data->order = create_matrix_order(data->nbr_of_philos);
	print_matrix(data->order, data->nbr_of_philos);//
	pthread_mutex_init(&(data->lock_print), NULL);
	pthread_mutex_init(&(data->lock_data), NULL);
}

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

t_args	*create_args(t_data *data, t_fork *forks)
{
	t_args	*args;
	int		i;

	args = malloc(sizeof(t_args) * data->nbr_of_philos);
	if (args == NULL)
		return (malloc_error());
	i = 0;
	while (i < data->nbr_of_philos)
	{
		args[i].nbr = i + 1;
		args[i].data = data;
		args[i].must_eat = data->nbr_of_times_must_eat;
		set_philo_forks(&args[i], forks, i, data->nbr_of_philos);
		if (data->order[0][i] == 1)
			args[i].next_eat = 0;
		else if (data->order[0][i] == 0 && data->order[1][i] == 1)
			args[i].next_eat = data->time.eating;
		else
			args[i].next_eat = 2 * data->time.eating;
		args[i].last_eat = 0;
		i++;
	}
	return (args);
}
