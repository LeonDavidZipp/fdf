/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/02 15:54:19 by lzipp            ###   ########.fr       */
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
			app_data->map[x][y]->projection = isometric_transform(
					app_data->map[x][y], scale);
			apply_offset(app_data->map[x][y]->projection, scale,
				x_scale, y_scale);
		}
	}
}

static t_line	*init_line(t_2d_point *start, t_2d_point *end)
{
	t_line	*line;

	line = ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	line->dx = fabs(end->x - start->x);
	line->dy = fabs(end->y - start->y);
	if (start->x < end->x)
		line->sx = 1;
	else
		line->sx = -1;
	if (start->y < end->y)
		line->sy = 1;
	else
		line->sy = -1;
	if (line->dx > line->dy)
		line->err = line->dx / 2;
	else
		line->err = -(line->dy / 2);
	line->x = start->x;
	line->y = start->y;
	line->e2 = line->err;
	return (line);
}

static void	draw_line(t_2d_point *start, t_2d_point *end, mlx_image_t *img)
{
	t_line		*line;

	line = init_line(start, end);
	while (!((line->sx > 0 && line->x > (uint32_t)end->x)
			|| (line->sx <= 0 && line->x < (uint32_t)end->x)
			|| (line->sy > 0 && line->y > (uint32_t)end->y)
			|| (line->sy <= 0 && line->y < (uint32_t)end->y)))
	{
		if (line->x <= img->width && line->y <= img->height
			&& line->x < end->x + start->x / 2)
			mlx_put_pixel(img, line->y, line->x, start->color);
		else if (line->x <= img->width && line->y <= img->height)
			mlx_put_pixel(img, line->y, line->x, end->color);
		if (line->e2 > -line->dx)
		{
			line->err -= line->dy;
			line->x += line->sx;
		}
		if (line->e2 < line->dy)
		{
			line->err += line->dx;
			line->y += line->sy;
		}
	}
	free(line);
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
