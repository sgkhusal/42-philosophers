/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/20 23:34:11 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo_args	*philosophers_args;
	pthread_t		*philosophers;
	t_fork			*forks;
	int				number_of_philosophers;

	if (handle_input(argc, argv) == FAILED)
		return (E_INVAL);
	number_of_philosophers = ft_atol(argv[1]);
	// se número de filósofos = 1: deve morrer - left_fork: problema!!
	// pode printar a mensagem de morte e fechar direto??
	forks = create_forks(number_of_philosophers);
	if (forks == NULL)
		return (E_MALLOC);
	philosophers_args = create_philosophers_args(number_of_philosophers,
			forks, argv);
	if (philosophers_args == NULL)
		return (E_MALLOC); // must clean
	philosophers = create_philosophers(number_of_philosophers,
			philosophers_args);
	if (philosophers == NULL)
		return (E_MALLOC); // must clean
	join_philosophers(philosophers, number_of_philosophers);
	// se algum filósofo morre tem que retornar algum erro?
	// como parar o programa se algum filósofo morre?
	return (0);
}
