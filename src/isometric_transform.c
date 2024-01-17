/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:31:55 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/17 14:09:09 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	free_projection(double **matrix)
{
	int			i;

	i = -1;
	while (++i < 3)
		free(matrix[i]);
	free(matrix);
}

static double	**make_projection1(void)
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

static double	**make_projection2(void)
{
	double	**matrix;

	matrix = ft_calloc(3, sizeof(double *));
	matrix[0] = ft_calloc(3, sizeof(double));
	matrix[1] = ft_calloc(3, sizeof(double));
	matrix[2] = ft_calloc(3, sizeof(double));
	matrix[1][0] = 1;
	matrix[1][1] = 1;
	return (matrix);
}

static t_3d_point	*multiply_projection1(t_3d_point *point)
{
	t_3d_point		*result;
	double			**projection1;

	result = ft_calloc(1, sizeof(t_3d_point));
	projection1 = make_projection1();
	if (!projection1 || !result)
	{
		free(result);
		free_projection(projection1);
		return (NULL);
	}
	result->x = 1 / sqrt(6) * (projection1[0][0] * point->x + projection1[0][1]
			* point->y + projection1[0][2] * point->z);
	result->y = 1 / sqrt(6) * (projection1[1][0] * point->x + projection1[1][1]
			* point->y + projection1[1][2] * point->z);
	result->z = 1 / sqrt(6) * (projection1[2][0] * point->x + projection1[2][1]
			* point->y + projection1[2][2] * point->z);
	result->color = point->color;
	free_projection(projection1);
	return (result);
}

t_2d_point	*isometric_transform(t_3d_point *point)
{
	t_3d_point		*temp;
	t_2d_point		*result;
	double			**projection2;

	temp = multiply_projection1(point);
	result = ft_calloc(1, sizeof(t_3d_point));
	projection2 = make_projection2();
	if (!projection2 || !result || !temp)
	{
		free(temp);
		free(result);
		free_projection(projection2);
		return (NULL);
	}
	result->x = projection2[0][0] * temp->x + projection2[0][1] * temp->y
		+ projection2[0][2] * temp->z;
	result->y = projection2[1][0] * temp->x + projection2[1][1] * temp->y
		+ projection2[1][2] * temp->z;
	result->color = temp->color;
	free(temp);
	free_projection(projection2);
	return (result);
}
