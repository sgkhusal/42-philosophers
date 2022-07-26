/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:01:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/26 18:29:19 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*create_forks(int number_of_forks)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * number_of_forks);
	if (forks == NULL)
		return (malloc_error());
	while (i < number_of_forks)
	{
		forks[i].status = FORK_AVAILABLE;
		i++;
	}
	return (forks);
}
