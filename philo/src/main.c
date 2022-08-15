/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:57:12 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/12 01:53:27 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	simulation_monitoring(t_args *philos, t_data *data)
{
	int			i;
	long long	delta;

	while (simulation(data) != STOP)
	{
		i = 0;
		//printf("last_eat = %lli\n", philos[i].last_eat);
		while (i < data->nbr_of_philos)
		{
			if (simulation(data) == STOP)
				break ;
			pthread_mutex_lock(&(philos[i].lock_philo));
			delta = time_now() - philos[i].last_eat;
			//printf("delta = %i\n", delta);
			if (delta >= data->time.to_die)
			{
				pthread_mutex_lock(&(data->lock_data));
				data->simulation = STOP;
				pthread_mutex_unlock(&(data->lock_data));
				usleep(100);
				philo_dies(i + 1, data->starting_time, data);
			}
			pthread_mutex_unlock(&(philos[i].lock_philo));
			i++;
		}
		usleep(100);
	}
}

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
	simulation_monitoring(args, &data);
	join_philos(philos, data.nbr_of_philos);
	// verificar se algum problema nos joins
	// se algum filósofo morre tem que retornar algum erro?
	// limpar forks, philos, args
	return (0);
}
