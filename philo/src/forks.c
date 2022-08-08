/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:01:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 12:11:33 by sguilher         ###   ########.fr       */
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
		forks[i].available = YES;
		i++;
	}
	return (forks);
}
