/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:11:17 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/12 02:19:44 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(long long time, int philo, char *action, t_data *data)
{
	if (simulation(data) == STOP)
			return ;
	pthread_mutex_lock(&(data->lock_print));
	printf("%-5lld %i %s\n", time, philo, action);
	pthread_mutex_unlock(&(data->lock_print));
}

int	simulation(t_data *data)
{
	int	simulation;

	pthread_mutex_lock(&(data->lock_data));
	simulation = data->simulation;
	pthread_mutex_unlock(&(data->lock_data));
	return (simulation);
}

void	set_simulation(t_data *data)
{
	if (simulation(data) != STOP)
	{
		pthread_mutex_lock(&(data->lock_data));
		data->simulation--;
		pthread_mutex_unlock(&(data->lock_data));
	}
}

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
