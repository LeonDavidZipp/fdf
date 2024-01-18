/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/18 19:07:01 by lzipp            ###   ########.fr       */
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

#include <stdio.h>
static void	draw_line(t_2d_point *point1, t_2d_point *point2,
	mlx_image_t *image)
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	int			color;

	dx = fabs(point2->x - point1->x);
	dy = fabs(point2->y - point1->y);
	x = point1->x;
	y = point1->y;
	color = point1->color;
	while (x != point2->x || y != point2->y)
	{
		printf("got here\n");
		mlx_put_pixel(image, (uint32_t)x, (uint32_t)y, (uint32_t)color);
		printf("got here too\n");
		if (x < point2->x)
			x++;
		if (x > point2->x)
			x--;
		if (y < point2->y)
			y++;
		if (y > point2->y)
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
	printf("1 draw\n");
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			printf("2 draw\n");
			if (app_data->map[x][y + 1])
				draw_line(app_data->map[x][y]->projection,
					app_data->map[x][y + 1]->projection,
					image);
			if (app_data->map[x + 1])
				draw_line(app_data->map[x][y]->projection,
					app_data->map[x + 1][y]->projection,
					image);
		}
	}
	mlx_image_to_window(app_data->mlx, image, 0, 0);
	printf("3 draw\n");
	// mlx_put_image_to_window(app_data->mlx, app_data->window,
	// 	app_data->image, 0, 0);
}
