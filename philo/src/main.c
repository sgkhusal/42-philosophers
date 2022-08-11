/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/11 14:30:23 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	pthread_t	*philos;
	t_fork		*forks;
	t_args		*args;
	t_data		data;

	if (handle_input(argc, argv, &data) == FAILED)
		return (E_INVAL);
	fill_data(&data);
	forks = create_forks(data.nbr_of_philos);
	if (forks == NULL)
		return (E_MALLOC);
	args = create_args(&data, forks);
	if (args == NULL)
		return (E_MALLOC); // must clean forks
	philos = create_philos(data.nbr_of_philos, args);
	if (philos == NULL)
		return (E_MALLOC); // must clean forks and philo_args
	join_philos(philos, data.nbr_of_philos);
	// verificar se algum problema nos joins
	// se algum filósofo morre tem que retornar algum erro?
	// como parar o programa se algum filósofo morre?
	// limpar forks, philos, args
	return (0);
}

// casos para testar:
// tempos = 0
// 5 100 0
// 5 0 0
