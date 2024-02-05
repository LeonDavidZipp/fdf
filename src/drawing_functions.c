/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 16:55:21 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	draw_line(t_2d_point *start, t_2d_point *end, mlx_image_t *img);
static void	draw_multiple_dots(t_app_data *a_d);
static void	draw_one_dot(t_2d_point *point, mlx_image_t *img);

void	draw_map(t_app_data *a_d)
{
	a_d->image = mlx_new_image(a_d->mlx, a_d->window_width, a_d->window_height);
	if (!a_d->image)
	{
		free_app_data(a_d);
		exit(1);
	}
	map_3d_to_2d(a_d);
	if (ft_null_terminated_arr_len((void **)a_d->map) == 1
		&& ft_null_terminated_arr_len((void **)a_d->map[0]) == 1)
		draw_one_dot(a_d->map[0][0]->projection, a_d->image);
	else
		draw_multiple_dots(a_d);
	mlx_image_to_window(a_d->mlx, a_d->image, 0, 0);
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
	return (line);
}

static void	draw_one_dot(t_2d_point *point, mlx_image_t *img)
{
	if (point->x <= img->height && point->y <= img->width)
		mlx_put_pixel(img, point->y, point->x, point->color);
	if (point->x + 1 <= img->height && point->y <= img->width)
		mlx_put_pixel(img, point->y, point->x + 1, point->color);
	if (point->x <= img->height && point->y + 1 <= img->width)
		mlx_put_pixel(img, point->y + 1, point->x, point->color);
	if (point->x - 1 <= img->height && point->y <= img->width)
		mlx_put_pixel(img, point->y, point->x - 1, point->color);
	if (point->x <= img->height && point->y - 1 <= img->width)
		mlx_put_pixel(img, point->y - 1, point->x, point->color);
}

static void	draw_multiple_dots(t_app_data *a_d)
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
		if (line->x <= img->height && line->y <= img->width)
			mlx_put_pixel(img, line->y, line->x, start->color);
		line->e2 = line->err;
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

// void	draw_map(t_app_data *a_d)
// {
// 	int	x;
// 	int	y;

// 	a_d->image = mlx_new_image(a_d->mlx, a_d->window_width, a_d->window_height);
// 	if (!a_d->image)
// 	{
// 		free_app_data(a_d);
// 		exit(1);
// 	}
// 	map_3d_to_2d(a_d);
// 	x = -1;
// 	while (a_d->map[++x])
// 	{
// 		y = -1;
// 		while (a_d->map[x][++y])
// 		{
// 			if (a_d->map[x][y + 1])
// 				draw_line(a_d->map[x][y]->projection, a_d->map[x][y + 1]
// 					->projection, a_d->image);
// 			if (a_d->map[x + 1])
// 				draw_line(a_d->map[x][y]->projection, a_d->map[x + 1][y]
// 					->projection, a_d->image);
// 		}
// 	}
// 	mlx_image_to_window(a_d->mlx, a_d->image, 0, 0);
// }
