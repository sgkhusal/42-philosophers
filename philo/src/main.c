/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 10:55:03 by sguilher         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	pthread_t	*philos;
	t_fork		*forks;
	t_args		*args;
	t_input		input;
	int			**order;

	if (handle_input(argc, argv, &input) == FAILED)
		return (E_INVAL);
	order = create_matrix_order(input.nbr_of_philos);
	print_matrix(order, input.nbr_of_philos);//
	forks = create_forks(input.nbr_of_philos);
	if (forks == NULL)
		return (E_MALLOC);
	args = create_args(input, forks, order);
	if (args == NULL)
		return (E_MALLOC); // must clean forks
	philos = create_philos(input.nbr_of_philos, args);
	if (philos == NULL)
		return (E_MALLOC); // must clean forks and philo_args
	join_philos(philos, input.nbr_of_philos);
	// verificar se algum problema nos joins
	// se algum filósofo morre tem que retornar algum erro?
	// como parar o programa se algum filósofo morre?
	// limpar forks, philos, args
	printf("End\n");
	return (0);
}

// casos para testar:
// tempos = 0
// 5 100 0
// 5 0 0
