/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:52:42 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/01 17:00:38 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	place_controls(mlx_t *mlx);

mlx_t	*make_window(void)
{
	mlx_t		*mlx;

	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(WIDTH, HEIGHT, "Leon's FDF", false);
	place_controls(mlx);
	return (mlx);
}

static void	place_controls(mlx_t *mlx)
{
	mlx_put_string(mlx, "ESC to exit", 10, 10);
}
