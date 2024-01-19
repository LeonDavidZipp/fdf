/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/19 15:44:35 by lzipp            ###   ########.fr       */
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

static void	apply_offset(t_2d_point *point, t_app_data *app_data, double offset)
{
	point->x += (app_data->window_width / 2);
	point->y += (app_data->window_height / 2);
}

static void	map_3d_to_2d(t_app_data *app_data)
{
	int				x;
	int				y;
	double			factor;
	double			temp;
	double			offset;

	factor = WIDTH / ft_null_terminated_arr_len((void **)app_data->map[0]);
	temp = HEIGHT / ft_null_terminated_arr_len((void **)app_data->map);
	if (factor > temp)
		factor = temp;
	x = -1;
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			app_data->map[x][y]->projection = ft_calloc(1, sizeof(t_2d_point));
			app_data->map[x][y]->projection = isometric_transform(
					app_data->map[x][y], factor);
			apply_offset(app_data->map[x][y]->projection, app_data);
		}
	}
}

#include <stdio.h>
static void	draw_line(t_2d_point *point1, t_2d_point *point2,
	mlx_image_t *image)
{
	uint32_t		x;
	uint32_t		y;
	int				color;

	x = (uint32_t)point1->x;
	y = (uint32_t)point1->y;
	color = point1->color;
	while (x != (uint32_t)point2->x || y != (uint32_t)point2->y)
	{
		mlx_put_pixel(image, x, y, (uint32_t)color);
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

	app_data->image = mlx_new_image(app_data->mlx, app_data->window_width,
			app_data->window_height);
	if (!app_data->image)
	{
		free_app_data(app_data);
		exit(1);
	}
	map_3d_to_2d(app_data);
	x = -1;
	printf("len = %d\n", ft_null_terminated_arr_len((void **)app_data->map[0]));
	while (app_data->map[++x])
	{
		y = -1;
		while (app_data->map[x][++y])
		{
			if (app_data->map[x][y + 1])
				draw_line(app_data->map[x][y]->projection,
					app_data->map[x][y + 1]->projection,
					app_data->image);
			if (app_data->map[x + 1])
				draw_line(app_data->map[x][y]->projection,
					app_data->map[x + 1][y]->projection,
					app_data->image);
		}
	}
	printf("len = %d\n", ft_null_terminated_arr_len((void **)app_data->map[0]));
	mlx_image_to_window(app_data->mlx, app_data->image, 0, 0);
}
