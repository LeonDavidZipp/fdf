/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:11 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/23 11:59:28 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_3d_point	*make_point(int x, int y, int z, int color);

static char	**get_values(char *line)
{
	char		**temp;
	char		**values;
	int			len;
	int			i;

	temp = ft_split(line, ' ');
	if (!temp)
		return (NULL);
	len = 0;
	while (temp[len] && temp[len][0] != '\n')
		len++;
	values = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (++i < len)
	{
		values[i] = ft_strdup(temp[i]);
		if (!values[i])
		{
			free_values(values);
			free_values(temp);
		}
	}
	free_values(temp);
	return (values);
}

static t_3d_point	**values_to_points(char **values, int row_num, int len)
{
	int			i;
	int			color;
	char		**value_n_color;
	t_3d_point	**row;

	row = ft_calloc(len + 1, sizeof(t_3d_point *));
	if (!row)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		value_n_color = ft_split(values[i], ',');
		if (!value_n_color)
			return (NULL);
		color = WHITE;
		if (ft_null_terminated_arr_len((void**)(value_n_color)) == 2)
			color = ft_hex_to_int(value_n_color[1]);
		row[i] = make_point(row_num, i, ft_atoi(value_n_color[0]), color);
		free_values(value_n_color);
		if (!row[i])
			return (NULL);
	}
	return (row);
}

static t_3d_point	*make_point(int x, int y, int z, int color)
{
	t_3d_point		*point;

	point = malloc(sizeof(t_3d_point));
	if (!point)
		return (NULL);
	point->x = (double)x;
	point->y = (double)y;
	point->z = (double)z;
	point->color = color;
	point->projection = NULL;
	return (point);
}
#include <stdio.h>
static t_3d_point	**make_row(char *line, int row_num)
{
	t_3d_point		**row;
	char			**values;
	int				len;

	values = get_values(line);
	if (!values)
		return (NULL);
	len = ft_null_terminated_arr_len((void **)values);
	row = values_to_points(values, row_num, len);
	len = -1;
	free_values(values);
	return (row);
}

t_3d_point	***make_map(int fd)
{
	int				row_num;
	char			*line;
	t_3d_point		***map;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	row_num = 0;
	map = ft_calloc(1, sizeof(t_3d_point **));
	while (line)
	{
		line = get_next_line(fd);
		map = ft_recalloc(map, (row_num + 1), sizeof(t_3d_point **));
		map[row_num] = make_row(line, row_num);
		row_num++;
	}
	return (map);
}

// cc make_map.c color_conversion.c free_functions.c ../lib/libft/ft_atoi.c 
// ../lib/libft/ft_null_terminated_arr_len.c ../lib/libft/ft_recalloc.c 
// ../lib/libft/ft_split.c ../lib/libft/ft_strdup.c ../lib/libft/ft_strrncmp.c 
// ../lib/get_next_line/get_next_line.c
// ../lib/get_next_line/get_next_line_utils.c ../lib/libft/ft_memmove.c
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
// 	t_3d_point ***map = make_map(fd);
// 	if (!map)
// 	{
// 		write(2, "Error\n", 6);
// 		close(fd);
// 		exit(1);
// 	}
// 	printf("Map created successfully.\n");
// 	int i = 0;
// 	int j;
// 	while (map[i] != NULL)
// 	{
// 		j = 0;
// 		while (map[i][j] != NULL)
// 		{
// 			printf("x: %f, y: %f, z: %f, color: %i\n",
// 				map[i][j]->x, map[i][j]->y, map[i][j]->z, map[i][j]->color);
// 			j++;
// 		}
// 		i++;
// 	}
// }
