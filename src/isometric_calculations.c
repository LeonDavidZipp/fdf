/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_calculations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:00:45 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/17 12:31:51 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_2d_point	*make_2d_point(int x, int y, int color)
{
	t_2d_point	*point;
	double		**matrix;

	matrix = make_matrix();
	point = ft_calloc(1, sizeof(t_2d_point));
	point->x = x;
	point->y = y;
	point->color = color;
	return (point);
}

void	rotate_x(t_3d_point *point, double angle)
{
	int	previous_y;
	int	previous_z;

	previous_y = point->y;
	previous_z = point->z;
	point->y = previous_y * cos(angle) + previous_z * sin(angle);
	point->z = -previous_y * sin(angle) + previous_z * cos(angle);
}

void	rotate_y(t_3d_point *point, double angle)
{
	int	previous_x;
	int	previous_z;

	previous_x = point->x;
	previous_z = point->z;
	point->x = previous_x * cos(angle) + previous_z * sin(angle);
	point->z = -previous_x * sin(angle) + previous_z * cos(angle);
}

void	rotate_z(t_3d_point *point, double angle)
{
	int	previous_x;
	int	previous_y;

	previous_x = point->x;
	previous_y = point->y;
	point->x = previous_x * cos(angle) - previous_y * sin(angle);
	point->y = previous_x * sin(angle) + previous_y * cos(angle);
}

void	rotate(t_3d_point *point, double x_angle, double y_angle, double z_angle)
{
	rotate_x(point, x_angle);
	rotate_y(point, y_angle);
	rotate_z(point, z_angle);
}

void	iso(t_3d_point *point)
{
	int	previous_x;
	int	previous_y;

	previous_x = point->x;
	previous_y = point->y;
	point->x = (previous_x - previous_y) * cos(0.523599);
	point->y = -point->z + (previous_x + previous_y) * sin(0.523599);
}

void	iso_map(t_3d_point ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			iso(map[i][j]);
			j++;
		}
		i++;
	}
}
