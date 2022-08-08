/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:38:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/08 10:56:27 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*only_one_philo_routine(void *philo_args)
{
	long long	delta_time;
	t_args		*args;

	args = (t_args *)philo_args;

	pthread_mutex_lock(&(args->right_fork->mutex));
	args->right_fork->status = FORK_NOT_AVAILABLE;
	delta_time = get_delta_time(args->init_time);
	printf("%lld 1 has taken a fork\n", delta_time);
	time_wait(args->input.time.to_die, args->init_time);
	philo_die(1, args->init_time);
	pthread_mutex_unlock(&(args->right_fork->mutex));
	return (philo_args);
}

/* void	wait_to_eat(t_args args, int *iteration)
{

}
 */
// TODO: lidar com os deltas ts == 0!!
void	*routine(void *philo_args)
{
	t_args	*args;

	args = (t_args *)philo_args;
	printf("Philo %i\n", args->nbr);

	return (philo_args);
}

// criar uma nova rotina, levando em conta o tempo para comer
// a cada time_eating + time_sleeping? -> passa a próxima linha da matrix
// iteration
