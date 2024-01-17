/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:31:55 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/17 12:32:33 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

double	**make_matrix(void)
{
	double	**matrix;

	matrix = ft_calloc(3, sizeof(double *));
	matrix[0] = ft_calloc(3, sizeof(double));
	matrix[1] = ft_calloc(3, sizeof(double));
	matrix[2] = ft_calloc(3, sizeof(double));
	matrix[0][0] = sqrt(3);
	matrix[0][2] = -sqrt(3);
	matrix[1][0] = 1;
	matrix[1][1] = 2;
	matrix[1][2] = 1;
	matrix[2][0] = sqrt(2);
	matrix[2][1] = -sqrt(2);
	matrix[2][2] = sqrt(2);
	return (matrix);
}

void	multiply_matrix(double **matrix1, double **matrix2)
{
	double	**result;
	int		i;
	int		j;
	int		k;

	result = ft_calloc(3, sizeof(double *));
	i = 0;
	while (i < 3)
	{
		result[i] = ft_calloc(3, sizeof(double));
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				result[i][j] += matrix1[i][k] * matrix2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	matrix1 = result;
}
