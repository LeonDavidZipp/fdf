/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/22 13:29:33 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>
// static void	apply_offset(t_2d_point *point, t_3d_point *base,
// 				t_app_data *app_data)
// {
// 	printf("base->x = %f\n", base->x);
// 	// point->x += (app_data->window_width / 2 + base->x);
// 	// point->y += (app_data->window_height / 2 + base->y);
// 	point->x += (app_data->window_width / 2);
// 	point->y += (app_data->window_height / 2);
// }

static void	apply_offset(t_2d_point *point, t_app_data *app_data,
		double x_offset, double y_offset)
{
	printf("x_offset = %f\n", x_offset);
	printf("y_offset = %f\n", y_offset);
	// point->x += (app_data->window_width / 2 - x_offset);
	// point->y += (app_data->window_height / 2 - y_offset);
	point->x += (app_data->window_width * 3 / 2 + x_offset * 10);
	point->y += (app_data->window_height *3 / 2 + y_offset * 10);
}

static void	map_3d_to_2d(t_app_data *app_data)
{
	int		x;
	int		y;
	double	x_scale;
	double	y_scale;
	double	factor;

	x_scale = app_data->image->width / ft_null_terminated_arr_len((void **)app_data->map[0]);
	y_scale = app_data->image->height / ft_null_terminated_arr_len((void **)app_data->map);
	factor = x_scale;
	if (factor > y_scale)
		factor = y_scale;
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			app_data->map[x][y]->projection = ft_calloc(1, sizeof(t_2d_point));
			app_data->map[x][y]->projection = isometric_transform(app_data->map[x][y],
					factor);
			apply_offset(app_data->map[x][y]->projection, app_data, factor
				* x_scale / WIDTH / 2, factor * y_scale / HEIGHT / 2);
		}
	}
}

#include <stdio.h>

// static void	draw_line(t_2d_point *point1, t_2d_point *point2,
// 	mlx_image_t *image)
// {
// 	uint32_t		x;
// 	uint32_t		y;
// 	int				color;

// 	x = (uint32_t)point1->x;
// 	y = (uint32_t)point1->y;
// 	color = point1->color;
// 	while (x != (uint32_t)point2->x || y != (uint32_t)point2->y)
// 	{
// 		mlx_put_pixel(image, y, x, (uint32_t)color);
// 		if (x < point2->x)
// 			x++;
// 		if (x > point2->x)
// 			x--;
// 		if (y < point2->y)
// 			y++;
// 		if (y > point2->y)
// 			y--;
// 	}
// }

void	draw_line(t_2d_point *start, t_2d_point *end, mlx_image_t *image)
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	uint32_t	x;
	uint32_t	y;

	dx = fabs(end->x - start->x);
	dy = fabs(end->y - start->y);
	sx = start->x < end->x ? 1 : -1;
	sy = start->y < end->y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	x = start->x;
	y = start->y;
	while (x <= (uint32_t)end->x && y <= (uint32_t)end->y)
	{
		if (x < image->width && y < image->height)
			mlx_put_pixel(image, y, x, start->color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
}

void	draw_map(t_app_data *app_data)
{
	int	x;
	int	y;

	app_data->image = mlx_new_image(app_data->mlx, app_data->window_width,
			app_data->window_height);
	if (!app_data->image)
	{
		free_app_data(app_data);
		exit(1);
	}
	map_3d_to_2d(app_data);
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			if (app_data->map[x][y + 1])
				draw_line(app_data->map[x][y]->projection, app_data->map[x][y
					+ 1]->projection, app_data->image);
			if (app_data->map[x + 1])
				draw_line(app_data->map[x][y]->projection, app_data->map[x
					+ 1][y]->projection, app_data->image);
		}
	}
	mlx_image_to_window(app_data->mlx, app_data->image, 0, 0);
}
