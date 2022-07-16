/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:01:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/16 00:02:01 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	*create_forks(int number_of_forks)
{
	int	i;
	int	*forks;

	i = 0;
	forks = malloc(sizeof(int) * number_of_forks);
	while (i < number_of_forks)
	{
		forks[i] = FORK_AVAILABLE;
		printf("fork %d = %d\n", i + 1, forks[i]);
		i++;
	}
	return (forks);
}
