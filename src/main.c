/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:26:22 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/31 14:57:58 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	check_valid_and_open(int argc, char **argv);

t_app_data	*init_app_data(void);

int	main(int argc, char **argv)
{
	int				fd;
	t_app_data		*app_data;

	fd = check_valid_and_open(argc, argv);
	app_data = init_app_data();
	app_data->map = make_map(fd);
	close(fd);
	app_data->mlx = make_window();
	draw_map(app_data);
	mlx_hook(app_data->mlx, 17, 0, &event_onclose, app_data);
	mlx_hook(app_data->mlx, 25, 0, &event_on_resize, app_data);
	mlx_loop(app_data->mlx);
	mlx_loop_hook(app_data->mlx, esc_hook, app_data);
	mlx_terminate(app_data->mlx);
	return (0);
}

static int	check_valid_and_open(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	if (ft_strrncmp(argv[1], ".fdf", 4) != 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (fd);
}

t_app_data	*init_app_data(void)
{
	t_app_data	*app_data;

	app_data = ft_calloc(1, sizeof(t_app_data));
	if (!app_data)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	app_data->window_width = WIDTH;
	app_data->window_height = HEIGHT;
	app_data->mlx = NULL;
	app_data->image = NULL;
	app_data->map = NULL;
	return (app_data);
}
