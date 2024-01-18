/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:52:42 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/18 10:07:34 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

mlx_t	*make_window(void)
{
	mlx_t		*mlx;

	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(WIDTH, HEIGHT, "Leon's FDF", true);
	return (mlx);
}

void	place_controls(t_app_data *app_data)
{
	mlx_put_string(app_data->mlx, "Controls:", 10, 10);
	mlx_put_string(app_data->mlx, "Use Arrow Keys to move", 10, 30);
	mlx_put_string(app_data->mlx, "ESC to exit", 10, 50);
	// mlx_put_string(app_data->mlx, "Scroll to zoom", 10, 70);
	// mlx_put_string(app_data->mlx, "R to reset", 10, 90);
}
