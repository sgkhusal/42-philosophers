/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/26 16:52:38 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	pthread_t	*philos;
	t_fork		*forks;
	t_args		*args;
	t_input		input;

	if (handle_input(argc, argv, &input) == FAILED)
		return (E_INVAL);
	forks = create_forks(input.nbr_of_philos);
	if (forks == NULL)
		return (E_MALLOC);
	args = create_args(input, forks);
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
	return (0);
}

// casos para testar:
// tempos = 0
