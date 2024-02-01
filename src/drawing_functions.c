/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/01 16:45:55 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

static void	apply_offset(t_2d_point *point, double x_offset, double y_offset)
{
	point->x += x_offset + 300;
	point->y += y_offset + 100;
}

// static double	calculate_scale(t_3d_point ***map)
// {
// 	int				i;
// 	int				j;
// 	int				x_max;
// 	int				y_max;
// 	int				y_min;
// 	t_2d_point		*point;

// 	i = -1;
// 	point = isometric_transform(map[0][0], 1);
// 	x_max = point->x;
// 	y_max = point->y;
// 	y_min = point->y;
// 	free(point);
// 	while (map[++i])
// 	{
// 		j = -1;
// 		while (map[i][++j])
// 		{
// 			point = isometric_transform(map[i][j], 1);
// 			if (point->x > x_max)
// 				x_max = point->x;
// 			if (point->y > y_max)
// 				y_max = point->y;
// 			if (point->y < y_min)
// 				y_min = point->y;
// 			free(point);
// 		}
// 	}
// }

static void	map_3d_to_2d(t_app_data *app_data)
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
			app_data->map[x][y]->projection = ft_calloc(1, sizeof(t_2d_point));
			app_data->map[x][y]->projection = isometric_transform(app_data->map[x][y],
					scale);
			apply_offset(app_data->map[x][y]->projection, scale
				* y_scale / WIDTH / 2, scale * x_scale / HEIGHT / 2);
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

void	draw_map(t_app_data *a_d)
{
	int	x;
	int	y;

	a_d->image = mlx_new_image(a_d->mlx, a_d->window_width, a_d->window_height);
	if (!a_d->image)
	{
		free_app_data(a_d);
		exit(1);
	}
	map_3d_to_2d(a_d);
	x = -1;
	while (a_d->map[++x])
	{
		y = -1;
		while (a_d->map[x][++y])
		{
			if (a_d->map[x][y + 1])
				draw_line(a_d->map[x][y]->projection, a_d->map[x][y + 1]
					->projection, a_d->image);
			if (a_d->map[x + 1])
				draw_line(a_d->map[x][y]->projection, a_d->map[x + 1][y]
					->projection, a_d->image);
		}
	}
	mlx_image_to_window(a_d->mlx, a_d->image, 0, 0);
}
