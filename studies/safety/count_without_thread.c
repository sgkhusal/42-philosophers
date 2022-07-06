/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_without_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:07:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/07/03 23:22:23 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

#define BIG 1000000000UL
uint32_t g_counter = 0;

void	count_to_big(void)
{
	for (uint32_t i = 0; i < BIG; i++)
		g_counter++;
}

int	main(void)
{
	count_to_big();
	count_to_big();
	printf("Done. Counter = %u\n", g_counter);
}

// time ./count_without_thread
// Done. Counter = 2000000000
// result = 5.169s
