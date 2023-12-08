/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:46 by lzipp             #+#    #+#             */
/*   Updated: 2023/12/08 11:33:29 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./src/libft/libft.h"
# include "./src/get_next_line/get_next_line.h"

# include <stdlib.h>
# include <unistd.h>
# include <math.h>

struct s_point {
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

struct s_map {
	s_point	**rows;
} t_map;

# define WIDTH 1920
# define HEIGHT 1080

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define PURPLE 0xFF00FF
# define CYAN 0x00FFFF
# define ORANGE 0xFFA500
# define PINK 0xFFC0CB
# define BROWN 0xA52A2A
# define GREY 0x808080
# define BLACK 0x000000

# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define PLUS 69
# define MINUS 78
# define NUM_PLUS 24
# define NUM_MINUS 27

#endif
