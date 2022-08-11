/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:38:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/11 15:35:02 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*only_one_philo_routine(void *args)
{
	long long	delta_time;
	t_args		*philo;

	philo = (t_args *)args;
	pthread_mutex_lock(&(philo->right_fork->lock));
	philo->right_fork->available = NO;
	delta_time = get_delta_time(philo->data->starting_time);
	print_action(delta_time, philo->nbr, "has taken a fork", &(philo->data->lock_print));
	time_wait(philo->data->time.to_die, philo->data->starting_time);
	philo_dies(1, philo->data->starting_time, &(philo->data->lock_print));
	pthread_mutex_unlock(&(philo->right_fork->lock));
	return (NULL);
}

/* void	wait_to_eat(t_args args, int *iteration)
{

}
 */
// TODO: lidar com os deltas ts == 0!!

int	simulation(t_args *philo)
{
	int	simulation;

	pthread_mutex_lock(&(philo->data->lock_data));
	simulation = philo->data->simulation;
	pthread_mutex_unlock(&(philo->data->lock_data));
	return (simulation);
}

void	*routine(void *args)
{
	t_args	*philo;

	philo = (t_args *)args;
	if (philo->next_eat != 0)
		usleep(philo->next_eat * 0.9 * 1000);
	//printf("Philo %i, simulation = %i, must_eat = %i\n", philo->nbr, philo->data->simulation, philo->must_eat);
	while (simulation(philo))
	{
		if (!philo->right_fork->available || !philo->left_fork->available)
		{
			usleep(500);
			continue ;
		}
		philo_eats(philo->nbr, philo->data->time.eating, philo);
		/* if (!philo->must_eat)
			break ; */
		if (simulation(philo) == STOP) // pode passar para a função de dormir
			break ;
		philo_sleeps(philo->nbr, philo->data->time.sleeping, philo->data->starting_time, &(philo->data->lock_print));
		if (simulation(philo) == STOP) // pode passar para a função de pensar
			break ;
		philo_thinks(philo->nbr, philo->data->starting_time, &(philo->data->lock_print));
		//wait_to_eat(philo->last_time_eating, philo->next_time_eating);
	}
	return (NULL);
}

// criar uma nova rotina, levando em conta o tempo para comer
// a cada time_eating + time_sleeping? -> passa a próxima linha da matrix
// iteration

void	philo_dies(int philo, long long starting_time, pthread_mutex_t *print)
{
	long long		delta_time;

	delta_time = get_delta_time(starting_time);
	print_action(delta_time, philo, "died", print);
}
