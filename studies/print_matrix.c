/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:06:32 by sguilher          #+#    #+#             */
/*   Updated: 2022/08/15 15:06:54 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	print_matrix(int **m, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%i ", m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
