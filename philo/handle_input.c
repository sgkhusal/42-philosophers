/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:17:50 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/15 20:37:24 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_input_error_message(void)
{
	printf(RED);
	printf("Invalid number of arguments. ");
	printf("To run philo use the following arguments:\n");
	printf(BLUE);
	printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] ");
	printf("[time_to_sleep] [number_of_times_each_philosopher_must_eat]");
	printf("(optional argument)\n");
	printf(RESET);
}

int	is_not_unsigned_int(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] == '+')
		i++;
	j = i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf(RED);
			printf("invalid argument: %s: must be a positive integer\n", str);
			printf(RESET);
			return (IS_NOT_VALID);
		}
		i++;
	}
	if (i - j > 11)
	{
		printf(RED);
		printf("invalid argument: %s: number too big\n", str);
		printf(RESET);
		return (IS_NOT_VALID);
	}
	return (IS_VALID);
}
// TODO: define if it is going to accept values with + and other input restrictions

int	handle_input(int argc, char *argv[])
{
	int	input_status;
	int	i;

	input_status = OK;
	if (argc < 5 || argc > 6)
	{
		print_input_error_message();
		input_status = FAILED;
	}
	i = 1;
	while (argv[i])
	{
		if (is_not_unsigned_int(argv[i]))
			input_status = FAILED;
		i++;
	}
	return (input_status);
}
