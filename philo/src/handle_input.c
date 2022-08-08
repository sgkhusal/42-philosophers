/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:17:50 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/27 00:19:46 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_input_error_message(void)
{
	printf(RED);
	printf("Invalid number of arguments. Run:\n");
	printf(BLUE);
	printf("./philo [nbr_of_philosophers] [time_to_die] [time_eating] "
		"[time_sleeping] [nbr_of_times_each_philosopher_must_eat](optional)\n");
	printf(RESET);
}

static int	check_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf(RED);
			printf("invalid argument: %s: must be a positive integer\n", str);
			printf(RESET);
			return (NOT_VALID);
		}
		i++;
	}
	if (i > 11 || ft_atol(str) > INT_MAX)
	{
		printf(RED);
		printf("invalid argument: %s: number too big\n", str);
		printf(RESET);
		return (NOT_VALID);
	}
	return (VALID);
}

static void	transform_input(int argc, char *argv[], t_input *input)
{
	input->nbr_of_philos = ft_atoi(argv[1]);
	input->time.to_die = ft_atoi(argv[2]);
	input->time.eating = ft_atoi(argv[3]);
	input->time.sleeping = ft_atoi(argv[4]);
	if (argc == 6)
		input->nbr_of_times_must_eat = ft_atoi(argv[5]);
	else
		input->nbr_of_times_must_eat = -1;
}

int	handle_input(int argc, char *argv[], t_input *input)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		print_input_error_message();
		return (FAILED);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		printf(RED);
		printf("Invalid number of philosophers.\n");
		printf(RESET);
		return (FAILED);
	}
	i = 1;
	while (argv[i])
	{
		if (check_valid_number(argv[i]) == NOT_VALID)
			return (FAILED);
		i++;
	}
	transform_input(argc, argv, input);
	return (OK);
}
