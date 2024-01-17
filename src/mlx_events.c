/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:15:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/17 14:15:43 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	event_onresize(int x, int y, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	vars->update = 1;
	vars->window_width = x;
	vars->window_height = y;
	mlx_resize_image(vars->image, x, y);
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
