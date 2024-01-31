/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:20:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/31 17:29:25 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

double	get_scale_2(int *x_max_y_max_ymin, t_3d_point ***map);

double	get_scale(t_3d_point ***map)
{
	int				i;
	int				j;
	double			x_max_y_max_ymin[3];
	t_2d_point		*point;

	point = isometric_transform(map[0][0], 1);
	x_max_y_max_ymin[0] = point->x;
	x_max_y_max_ymin[1] = point->y;
	x_max_y_max_ymin[2] = point->y;
	free(point);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			point = isometric_transform(map[i][j], 1);
			if (point->x > x_max_y_max_ymin[0])
				x_max_y_max_ymin[0] = point->x;
			if (point->y > x_max_y_max_ymin[1])
				x_max_y_max_ymin[1] = point->y;
			else if (point->y < x_max_y_max_ymin[2])
				x_max_y_max_ymin[2] = point->y;
			free(point);
		}
	}
	get_scale_2(x_max_y_max_ymin, map);
}

double	get_scale_2(int *x_max_y_max_ymin, t_3d_point ***map)
{
	double			x_diff;
	double			y_diff;

	x_diff = x_max_y_max_ymin[0];
	y_diff = x_max_y_max_ymin[1] - x_max_y_max_ymin[2];
}
