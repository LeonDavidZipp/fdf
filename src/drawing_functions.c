/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/18 13:57:46 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	apply_offset(t_2d_point *point, t_3d_point *base, t_app_data *app_data)
{
	point->x += app_data->window_width / 2 + base->x;
	point->y += app_data->window_height / 2 + base->y;
}


void	draw_map(t_3d_point ***map, t_app_data *app_data)
{
	int	x;
	int	y;

	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (x != map->width - 1)
				ft_draw_line(project(x, y, env), project(x + 1, y, env), env);
			if (y != map->height - 1)
				ft_draw_line(project(x, y, env), project(x, y + 1, env), env);
			x += -2 * (env->camera->y_angle > 0) + 1;
		}
		y += -2 * (env->camera->x_angle > 0) + 1;
	}
	mlx_put_image_to_window(app_data->mlx, app_data->win, app_data->image, 0, 0);
	ft_draw_instructions(env);
}


