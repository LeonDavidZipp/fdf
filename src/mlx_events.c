/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:15:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/18 10:16:38 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	event_onresize(int x, int y, void *app_data)
{
	t_app_data		*new_data;

	new_data = (t_app_data *)app_data;
	new_data->update = 1;
	new_data->window_width = x;
	new_data->window_height = y;
	mlx_resize_image(new_data->image, x, y);
}

void	event_onclose(void *param)
{
	t_vars	*vars;
	int		x;

	x = -1;
	vars = (t_vars *)param;
	write(1, "\nClosing window...\n", 20);
	while (++x < vars->map->size_y)
		free(vars->map->points[x]);
	free(vars->map->points);
	free(vars->map);
	mlx_delete_image(vars->mlx, vars->image);
	mlx_terminate(vars->mlx);
	ft_exit(0);
}

void	event_onfail(void *param, int rows)
{
	t_vars	*vars;
	int		x;

	x = -1;
	vars = (t_vars *)param;
	while (++x < rows)
		free(vars->map->points[x]);
	free(vars->map->points);
	free(vars->map);
	mlx_terminate(vars->mlx);
	write(1, "Woops! Something failed to initialize. Closing window\n", 55);
	ft_exit(0);
}
