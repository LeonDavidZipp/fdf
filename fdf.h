/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:46 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/02 12:43:05 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// includes
# include "./lib/MLX42/include/MLX42/MLX42.h"
# include "./lib/get_next_line/get_next_line.h"
# include "./lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>

// defines
# define WIDTH 1080
# define HEIGHT 1080
# define WHITE 0xFFFFFF

// structs
typedef struct s_2d_point
{
	double		x;
	double		y;
	int			color;
}				t_2d_point;

typedef struct s_3d_point
{
	double		x;
	double		y;
	double		z;
	int			color;
	t_2d_point	*projection;
}				t_3d_point;

typedef struct s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	uint32_t	x;
	uint32_t	y;
}				t_line;

typedef struct s_app_data
{
	mlx_t		*mlx;
	void		*window;
	mlx_image_t	*image;
	t_3d_point	***map;
	int			window_width;
	int			window_height;
}				t_app_data;

int				ft_hex_to_int(char *hex_char);
int				int_to_r(int hex);
int				int_to_g(int hex);
int				int_to_b(int hex);

// map generation functions
t_3d_point		***make_map(int fd);

// isometric functions
t_2d_point		*isometric_transform(t_3d_point *point, double scale);

// free functions
void			free_values(char **values);
void			free_map(t_3d_point ***map);
void			free_app_data(t_app_data *app_data);

// gui
mlx_t			*make_window(void);
void			draw_map(t_app_data *app_data);

// loops & hooks
void			esc_hook(void	*data);
void			event_on_resize(int x, int y, t_app_data *app_data);
void			event_onclose(t_app_data *app_data);
void			event_onfail(t_app_data *app_data);

#endif
