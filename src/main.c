/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:26:22 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/02 12:53:38 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	check_valid_and_open(int argc, char **argv);
t_app_data	*init_app_data(int fd);
void		esc_hook(void	*data);

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

t_app_data	*init_app_data(int fd)
{
	t_app_data	*app_data;

	app_data = ft_calloc(1, sizeof(t_app_data));
	if (!app_data)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	app_data->mlx = make_window();
	app_data->map = make_map(fd);
	app_data->image = NULL;
	app_data->window_width = WIDTH;
	app_data->window_height = HEIGHT;
	return (app_data);
}

void	esc_hook(void	*data)
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
