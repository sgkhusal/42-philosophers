/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/22 19:09:47 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo_args	*philos_args;
	pthread_t		*philos;
	t_fork			*forks;
	t_input			input;

	if (handle_input(argc, argv, &input) == FAILED)
		return (E_INVAL);
	forks = create_forks(input.nbr_of_philos);
	if (forks == NULL)
		return (E_MALLOC);
	philos_args = create_philos_args(input, forks);
	if (philos_args == NULL)
		return (E_MALLOC); // must clean forks
	philos = create_philos(input.nbr_of_philos, philos_args);
	if (philos == NULL)
		return (E_MALLOC); // must clean forks and philo_args
	join_philos(philos, input.nbr_of_philos);
	// verificar se algum problema nos joins
	// se algum filósofo morre tem que retornar algum erro?
	// como parar o programa se algum filósofo morre?
	// limpar forks, philos, philos_args
	return (0);
}

// casos para testar:
// tempos = 0
