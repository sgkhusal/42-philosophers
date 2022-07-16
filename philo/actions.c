/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:58:42 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/15 23:59:04 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(int philosopher)
{
	printf("timestamp_in_ms %i is eating\n", philosopher);
}

void	*routine(void *arg)
{
	int	*philosopher;

	philosopher = (int *)arg;
	printf("Hello\n");
	printf("timestamp_in_ms %i has taken a fork\n", *philosopher);
	printf("timestamp_in_ms %i has taken a fork\n", *philosopher);
	eat(*philosopher);
	printf("timestamp_in_ms %i is sleeping\n", *philosopher);
	printf("timestamp_in_ms %i is thinking\n", *philosopher);
	return ("tchau");
}
