/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:32:58 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/06 16:01:01 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_point	*make_point(int x, int y, int z, int color)
{
	t_point		*point;

	point = ft_calloc(1, sizeof(t_point));
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

static t_point	*make_row(char *lines, int width, int *i)
{
	t_point		*row;
	int			x;
	int			y;
	int			z;
	char		**split_line;

	row = ft_calloc(width + 1, sizeof(t_point));
	split_line = ft_split(lines, ' ');
	while (split_line[*i])
	{
		row[*i] = *make_point(i, *i, ft_atoi(split_line[*i]), WHITE);
		i++;
	}
	row[*i] = *make_point(i, *i, 0, WHITE);
	*i++;
	return (row);
}

t_map	*make_map(char *filename)
{
	char	*lines;
	char	**values;
	int		i;
	int		row;
	int		col;
	int		width;
	int		height;
	t_map	*map;

	lines = read_lines_from_file(filename);
	if (!lines)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	values = ft_split(lines, ' ');
	width = get_width(lines);
	height = get_height(lines);
	free(lines);
	if (!values)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	i = 0;
	map = ft_calloc(map->height + 1, sizeof(t_point *));
	if (!map)
	{
		free(values);
		write(1, "Error\n", 6);
		exit(1);
	}
	map->height = height;
	map->width = width;
	row = 0;
	while (values[i])
	{
		col = 0;
		while (values[i] != '\n')
		{
			map[row] = ft_calloc(map->width + 1, sizeof(t_point));
			map[row][col] = *make_point(col, row, ft_atoi(values[i]), WHITE);
			col++;
			i++;
		}
		row++;
		i++;
	}
	free(values);
	return (map);
}

// t_map	make_map(int fd)
// {
// 	t_map		map;
// 	char		*line;
// 	char		**split_line;
// 	int			i;
// 	int			j;

// 	map.rows = ft_calloc(1, sizeof(t_point *));
// 	i = 0;
// 	while (get_next_line(fd, &line))
// 	{
// 		split_line = ft_split(line, ' ');
// 		map.rows[i] = ft_calloc(ft_arrlen(split_line) + 1, sizeof(t_point));
// 		j = 0;
// 		while (split_line[j])
// 		{
// 			map.rows[i][j] = *make_point(j, i, ft_atoi(split_line[j]), WHITE);
// 			j++;
// 		}
// 		map.rows[i][j] = *make_point(j, i, 0, WHITE);
// 		i++;
// 	}
// 	map.rows[i] = NULL;
// 	return (map);
// }
