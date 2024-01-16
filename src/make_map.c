/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:11 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/16 16:45:30 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_point	*make_point(int x, int y, int z, int color);

static void	values_to_points(char **values, t_point **row, int row_num, int len)
{
	int			i;
	int			color;
	char		**value_n_color;

	i = -1;
	while (++i < len)
	{
		value_n_color = ft_split(values[i], ',');
		if (!value_n_color)
			return ;
		color = WHITE;
		if (ft_null_terminated_arr_len(value_n_color) == 2)
			color = ft_hex_to_int(value_n_color[1]);
		row[i] = make_point(row_num, i, ft_atoi(value_n_color[0]), color);
		free_values(value_n_color);
	}
}

static t_point	*make_point(int x, int y, int z, int color)
{
	t_point		*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

static t_point	**make_row(char *line, int row_num)
{
	t_point		**row;
	char		**values;
	int			len;

	values = get_values(line);
	if (!values)
		return (NULL);
	len = ft_null_terminated_arr_len(values);
	row = ft_calloc(len + 1, sizeof(t_point *));
	if (!row)
	{
		free_values(values);
		return (NULL);
	}
	values_to_points(values, row, row_num, len);
	free_values(values);
	return (row);
}

t_point	***make_map(int fd)
{
	int			row_num;
	char		*line;
	t_point		***map;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	row_num = 0;
	map = ft_calloc(1, sizeof(t_point **));
	while (line)
	{
		line = get_next_line(fd);
		map = ft_recalloc(map, (row_num + 1), sizeof(t_point **));
		map[row_num] = make_row(line, row_num);
		if (!map[row_num])
		{
			free_map(map);
			return (NULL);
		}
		row_num++;
	}
	return (map);
}

// cc make_map.c free_functions.c libft/ft_atoi.c color_conversion.c libft/ft_null_terminated_arr_len.c libft/ft_recalloc.c libft/ft_split.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft/ft_memmove.c
// #include <stdio.h>
// int main(void)
// {
// 	char *filename = "../test_maps/elem-col.fdf";
// 	int fd = open(filename, O_RDONLY);
// 	if (ft_strrncmp(filename, ".fdf", 4) != 0 || fd < 0)
// 	{
// 		write(2, "Error\n", 6);
// 		close(fd);
// 		exit(1);
// 	}
// 	t_point ***map = make_map(filename);
// 	printf("Map created successfully.\n");
// 	int i = 0;
// 	int j;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			printf("x: %d, y: %d, z: %d, color: %d\n", map[i][j]->x, map[i][j]->y, map[i][j]->z, map[i][j]->color);
// 			j++;
// 		}
// 		i++;
// 	}
// }
