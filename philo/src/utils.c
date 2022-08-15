/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:11:17 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/15 15:10:58 by sguilher         ###   ########.fr       */
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
	int	i;

	printf("Error creating philo %i thread.\n", philo_nbr);
	i = 0;
	while (i < philo_nbr)
	{
		pthread_detach(philos[i]);
		i++;
	}
	free (philos);
	return (NULL);
}
