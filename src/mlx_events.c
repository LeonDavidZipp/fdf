/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:15:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/18 18:04:32 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	event_on_resize(int x, int y, t_app_data *app_data)
{
	app_data->window_width = x;
	app_data->window_height = y;
	mlx_resize_image(app_data->image, x, y);
}

void	event_onclose(t_app_data *app_data)
{
	write(1, "\nClosing window...\n", 20);
	free_map(app_data->map);
	mlx_delete_image(app_data->mlx, app_data->image);
	mlx_terminate(app_data->mlx);
	exit(0);
}

void	event_onfail(t_app_data *app_data, int rows)
{
	free_map(app_data->map);
	mlx_terminate(app_data->mlx);
	write(1, "\nError while initializing. Closing window...\n", 46);
	exit(1);
}
