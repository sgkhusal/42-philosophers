/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:38:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/27 23:33:54 by sguilher         ###   ########.fr       */
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
	delta_time = get_delta_time(args->init_tv);
	printf("%lld 1 has taken a fork\n", delta_time);
	time_wait(args->time_to_die, args->init_tv);
	philo_die(1, args->init_tv);
	pthread_mutex_unlock(&(args->right_fork->mutex));
	return ("died"); // mudar retorno
}

int	preparation(t_args args)
{
	int	iteration;

	iteration = 1;
	if (args.nbr % 2 == 0)
	{
		usleep(args.time_eating * 0.9 * 1000); // verificar um valor bom
		iteration++;
	}
	if (args.nbr % 2 == 1 && args.is_last_philo)
	{
		usleep(args.time_eating * 1.9 * 1000); // verificar um valor bom
		iteration += 2;
	}
	return (iteration);
}

void	wait_to_eat(t_args args, int *iteration)
{
	if (args.time_sleeping < args.time_eating) // + x ?
		usleep((args.time_eating - args.time_sleeping) * 0.9 * 1000); // verificar um valor bom
	(*iteration)++;
	if (args.order[(*iteration - 1) % args.nbr_of_philos][args.nbr - 1] == 0)
	{
		if (args.time_sleeping > args.time_eating) // + x ?
			usleep((2 * args.time_eating - args.time_sleeping) * 0.9 * 1000);
		else
			usleep(args.time_eating * 0.9 * 1000);
		(*iteration)++;
	}
	/* if (args.is_first_philo || (args.nbr % 2 == 1 && args.is_last_philo))
		usleep(args.time_eating * 0.9 * 1000); */
}

// TODO: lidar com os deltas ts == 0!!
void	*routine(void *philo_args)
{
	t_args	*args;
	int		philo_alive;
	int		iteration;

	args = (t_args *)philo_args;
	iteration = preparation(*args);
	philo_alive = 10; // alterar
	while (philo_alive && args->nbr_of_times_must_eat) // enquanto não morre
	{
		if (args->right_fork->status == FORK_NOT_AVAILABLE || args->left_fork->status == FORK_NOT_AVAILABLE)
		{
			// checar se o philosofo morre
			usleep(500); // talvez seja útil se todos começarem a morrer
			continue ;
		}
		philo_eat(args->nbr, args->time_eating, args);
		args->nbr_of_times_must_eat--;
		iteration++;
		if (!args->nbr_of_times_must_eat) //
			break ;
		philo_sleep(args->nbr, args->time_sleeping, args->init_tv);
		philo_think(args->nbr, args->init_tv);
		wait_to_eat(*args, &iteration);
		//philo_alive--; //
	}
	if (!philo_alive)
	{
		philo_die(args->nbr, args->init_tv);
		return ("died");
	}
	return ("bye");
}

// criar uma nova rotina, levando em conta o tempo para comer
// a cada time_eating + time_sleeping? -> passa a próxima linha da matrix
// iteration
