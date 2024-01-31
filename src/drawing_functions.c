/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/31 13:38:30 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

static void	apply_offset(t_2d_point *point, // t_app_data *app_data,
		double x_offset, double y_offset)
{
	point->x += x_offset;
	point->y += y_offset;
}

static void	map_3d_to_2d(t_app_data *app_data)
{
	int		x;
	int		y;
	double	x_scale;
	double	y_scale;
	double	scale;
	double	x_offset;
	double	y_offset;

	x_scale = WIDTH / ft_null_terminated_arr_len((void **)app_data->map[0]);
	y_scale = HEIGHT / ft_null_terminated_arr_len((void **)app_data->map);
	scale = x_scale;
	if (scale > y_scale)
		scale = y_scale;
	x_offset = (app_data->image->width - scale * ft_null_terminated_arr_len((void **)app_data->map[0])) / 2;
	y_offset = (app_data->image->height - scale * ft_null_terminated_arr_len((void **)app_data->map)) / 2;
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			app_data->map[x][y]->projection = ft_calloc(1, sizeof(t_2d_point));
			app_data->map[x][y]->projection = isometric_transform(app_data->map[x][y],
					scale);
			apply_offset(app_data->map[x][y]->projection, x_offset, y_offset);
		}
		y = 0;
		while (app_data->map[x][y] && app_data->map[x][y]->projection != NULL)
		{
			printf("x %d y %d projection_x %f projection_y %f\n\n", x, y,
				app_data->map[x][y]->projection->x,
				app_data->map[x][y]->projection->y);
			y++;
		}
		printf("image width %d height %d\n", app_data->image->width,
			app_data->image->height);
	}
}

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
	if (start->x < end->x)
		sx = 1;
	else
		sx = -1;
	if (start->y < end->y)
		sy = 1;
	else
		sy = -1;
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	x = start->x;
	y = start->y;
	// printf("width %d height %d\n", image->width, image->height);
	// while (x <= (uint32_t)end->x && y <= (uint32_t)end->y)
	while (true)
	{
		if (sx > 0 && x > (uint32_t)end->x)
			break ;
		if (sx <= 0 && x < (uint32_t)end->x)
			break ;
		if (sy > 0 && y > (uint32_t)end->y)
			break ;
		if (sy <= 0 && y < (uint32_t)end->y)
			break ;
		// printf("x %d y %d\n", x, y);
		if (x <= image->width && y <= image->height)
			mlx_put_pixel(image, y, x, start->color);
		e2 = err;
		// printf("e2 %d -dx %d\n", e2, -dx);
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		// printf("e2 %d dy %d\n", e2, dy);
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
		// break ;
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
	printf("map_converted\n");
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
	printf("im width: %d\n", app_data->image->width);
	mlx_image_to_window(app_data->mlx, app_data->image, 0, 0);
}
