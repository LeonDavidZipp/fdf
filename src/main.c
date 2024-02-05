/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:26:22 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 12:09:40 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int			check_valid_and_open(int argc, char **argv);
static t_app_data	*init_app_data(int fd);
static void			esc_hook(void *data);
static mlx_t		*make_window(int window_width, int window_height);

int	main(int argc, char **argv)
{
	int				fd;
	t_app_data		*app_data;

	fd = check_valid_and_open(argc, argv);
	app_data = init_app_data(fd);
	close(fd);
	draw_map(app_data);
	mlx_loop_hook(app_data->mlx, esc_hook, app_data);
	mlx_loop(app_data->mlx);
	mlx_terminate(app_data->mlx);
	free_app_data(app_data);
	return (0);
}

static int	check_valid_and_open(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		write(2, "Error: Wrong number of arguments.\n", 34);
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".fdf", 4) != 0)
	{
		write(2, "Error: Wrong file type.\n", 24);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Couldn't open or read from file.\n", 40);
		exit(1);
	}
	return (fd);
}

static t_app_data	*init_app_data(int fd)
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
	app_data->mlx = make_window(app_data->window_width,
			app_data->window_height);
	app_data->map = make_map(fd);
	app_data->image = NULL;
	check_map_valid(app_data);
	return (app_data);
}

static void	esc_hook(void *data)
{
	t_app_data		*app_data;

	app_data = (t_app_data *)data;
	if (mlx_is_key_down(app_data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(app_data->mlx);
		free_app_data(app_data);
		exit(0);
	}
}

static mlx_t	*make_window(int window_width, int window_height)
{
	mlx_t		*mlx;

	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(window_width, window_height, "Leon's FDF", false);
	mlx_put_string(mlx, "ESC to exit", 10, 10);
	return (mlx);
}
