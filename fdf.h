/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:46 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/22 12:28:01 by lzipp            ###   ########.fr       */
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
# define WIDTH 1920 * 2
# define HEIGHT 1080 * 2

# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define PLUS 69
# define MINUS 78
# define NUM_PLUS 24
# define NUM_MINUS 27

# define WHITE 0xFFFFFF

# define INITIAL_RADIUS 5

// structs
typedef struct s_2d_point
{
	double		x;
	double		y;
	double		radius;
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
	t_2d_point	*start;
	t_2d_point	*end;
	double		dx;
	double		dy;
	double		x1_greater_x2;
	double		y1_greater_y2;
	double		decision_param;
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
// mlx_t			*make_window(t_app_data *app_data);
mlx_t			*make_window(void);
void			draw_map(t_app_data *app_data);

#endif
