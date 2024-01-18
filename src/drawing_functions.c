/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/18 17:31:24 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	apply_offset(t_2d_point *point, t_3d_point *base,
				t_app_data *app_data)
{
	point->x += (app_data->window_width / 2 + base->x) * 10;
	point->y += (app_data->window_height / 2 + base->y) * 10;
}

static void	map_3d_to_2d(t_app_data *app_data)
{
	int		x;
	int		y;

	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			app_data->map[x][y]->projection = ft_calloc(1, sizeof(t_2d_point));
			app_data->map[x][y]->projection = isometric_transform(
					app_data->map[x][y]);
			apply_offset(app_data->map[x][y]->projection,
				app_data->map[x][y], app_data);
		}
	}
}

static void	draw_line(t_2d_point *p1, t_2d_point *p2, t_app_data *app_data,
		mlx_image_t *image)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		color;

	dx = abs(p2->x - p1->x);
	dy = abs(p2->y - p1->y);
	x = p1->x;
	y = p1->y;
	color = p1->color;
	while (x != p2->x || y != p2->y)
	{
		mlx_pixel_put_image(image, x, y, color);
		if (x < p2->x)
			x++;
		if (x > p2->x)
			x--;
		if (y < p2->y)
			y++;
		if (y > p2->y)
			y--;
	}
}

void	draw_map(t_app_data *app_data)
{
	int			x;
	int			y;
	mlx_image_t	*image;

	image = mlx_new_image(app_data->mlx, app_data->window_width,
			app_data->window_height);
	map_3d_to_2d(app_data);
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			if (app_data->map[x][y + 1])
				draw_line(app_data->map[x][y]->projection,
					app_data->map[x][y + 1]->projection,
					app_data, image);
			if (app_data->map[x + 1])
				draw_line(app_data->map[x][y]->projection,
					app_data->map[x + 1][y]->projection,
					app_data, image);
		}
	}
	mlx_put_image_to_window(app_data->mlx, app_data->window,
		app_data->image, 0, 0);
}
