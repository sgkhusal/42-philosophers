/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:38:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 16:37:20 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*only_one_philo_routine(void *philo_args)
{
	long long	delta_time;
	t_args		*args;

	args = (t_args *)philo_args;
	pthread_mutex_lock(&(args->right_fork->mutex));
	args->right_fork->available = NO;
	delta_time = get_delta_time(args->init_time);
	printf("%lld 1 has taken a fork\n", delta_time);
	time_wait(args->time.to_die, args->init_time);
	philo_dies(1, args->init_time, args->print);
	pthread_mutex_unlock(&(args->right_fork->mutex));
	return (philo_args);
}

/* void	wait_to_eat(t_args args, int *iteration)
{

}
 */
// TODO: lidar com os deltas ts == 0!!
void	*routine(void *args)
{
	t_args	*philo;

	philo = (t_args *)args;
	if (philo->next_time_eating != 0)
		usleep(philo->next_time_eating * 0.9 * 1000);
	while (philo->must_eat && *(philo->simulation)) // verificar o valor de (*)philo->simulation
	{
		if (!philo->right_fork->available || !philo->left_fork->available)
		{
			usleep(500);
			continue ;
		}
		philo_eats(philo->nbr, philo->time.eating, philo);
		if (philo->must_eat == NO)
		{
			//mutex_lock?
			//*(philo->simulation)--;
		}
		if (philo->must_eat == NO && *(philo->simulation) == STOP) //
			break ;
		philo_sleeps(philo->nbr, philo->time.sleeping, philo->init_time, philo->print);
		if (*(philo->simulation) == STOP) //
			break ;
		philo_thinks(philo->nbr, philo->init_time, philo->print);
		if (*(philo->simulation) == STOP) //
			break ;
		//wait_to_eat(philo->last_time_eating, philo->next_time_eating);
	}
	return (args);
}

// criar uma nova rotina, levando em conta o tempo para comer
// a cada time_eating + time_sleeping? -> passa a próxima linha da matrix
// iteration
