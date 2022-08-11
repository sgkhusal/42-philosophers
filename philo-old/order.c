/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:03:19 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/27 02:03:58 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_even_matrix_order(int **m, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i % 2 == 0 && j % 2 == 0)
				m[i][j] = 1;
			else if (i % 2 == 1 && j % 2 == 1)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	fill_odd_matrix_order(int **m, int size)
{
	int	i;
	int	j;

	fill_even_matrix_order(m, size);
	m[0][size - 1] = 0;
	i = 2;
	while (i < size)
	{
		j = i - 2;
		while (j >= 0)
		{
			if (i % 2 == 1 && j % 2 == 0)
				m[i][j] = 1;
			else if (i % 2 == 0 && j % 2 == 1)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j--;
		}
		i++;
	}
}

int	**create_matrix_order(int nbr_of_philos)
{
	int	**order;
	int	i;

	order = malloc(sizeof(int *) * nbr_of_philos);
	if (order == NULL)
		return (malloc_error());
	i = 0;
	while (i < nbr_of_philos)
	{
		order[i] = malloc(sizeof(int) * nbr_of_philos);
		i++;
	}
	i = 0;
	if (nbr_of_philos % 2 == 0)
		fill_even_matrix_order(order, nbr_of_philos);
	else
		fill_odd_matrix_order(order, nbr_of_philos);
	return (order);
}
