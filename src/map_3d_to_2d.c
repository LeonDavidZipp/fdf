/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3d_to_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:17:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 15:42:03 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	apply_offset(t_2d_point *point, double scale,
	double x_scale, double y_scale)
{
	double	x_offset;
	double	y_offset;

	x_offset = scale * x_scale / HEIGHT / 2 + 600;
	y_offset = scale * y_scale / WIDTH / 2 + 200;
	point->x += x_offset;
	point->y += y_offset;
}

void	map_3d_to_2d(t_app_data *app_data)
{
	int		x;
	int		y;
	double	x_scale;
	double	y_scale;
	double	scale;

	x_scale = WIDTH / ft_null_terminated_arr_len((void **)app_data->map[0]);
	y_scale = HEIGHT / ft_null_terminated_arr_len((void **)app_data->map);
	scale = x_scale / 2;
	if (scale > y_scale / 2)
		scale = y_scale / 2;
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			app_data->map[x][y]->projection = isometric_transform(
					app_data->map[x][y], scale);
			apply_offset(app_data->map[x][y]->projection, scale,
				x_scale, y_scale);
		}
	}
}
