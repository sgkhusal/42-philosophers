/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:11:17 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/26 20:15:52 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*malloc_error(void)
{
	write(2, "Malloc error.\n", 15);
	return (NULL);
}

void	*pthread_error(pthread_t *philos, int philo_nbr)
{
	printf("Error creating philo %i thread.\n", philo_nbr);
	free (philos); // tá certo fazer isso antes de dar free nas outras threads?
	return (NULL);
}
