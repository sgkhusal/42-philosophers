/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:17:50 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/12 01:08:22 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	input_error(char *str, char *error)
{
	printf("%sinvalid argument: %s: %s%s\n", RED, str, error, RESET);
	return (NOT_VALID);
}

static void	print_input_error_message(void)
{
	printf("%sInvalid number of arguments. Run:\n%s", RED, BLUE);
	printf("./philo [nbr_of_philosophers] [time_to_die] [time_eating] "
		"[time_sleeping] [nbr_of_times_each_philosopher_must_eat](optional)\n");
	printf(RESET);
}

static int	check_valid_number(char *str)
{
	int	i;
	int	nb;

	i = 0;
	if (str[i] && str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (input_error(str, "must be a positive integer"));
		i++;
	}
	nb = ft_atol(str);
	if (nb == 0)
		return (input_error(str, "number must be greater than zero"));
	if (i > 11 || nb > INT_MAX)
		return (input_error(str, "number too big"));
	return (VALID);
}

static void	transform_input(int argc, char *argv[], t_data *input)
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

int	handle_input(int argc, char *argv[], t_data *input)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		print_input_error_message();
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
