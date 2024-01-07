/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:32:58 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/07 15:14:17 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static char	**get_values(char *filename)
{
	char	*lines;
	char	**values;

	lines = read_lines_from_file(filename);
	values = ft_split(lines, ' ');
	free(lines);
	if (!values)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (values);
}

static void	free_values(char **values)
{
	int		i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
	exit(1);
}

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

#include <stdio.h>
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
	values = ft_split(lines, ' ');
	width = get_width(lines);
	height = get_height(lines);
	free(lines);
	if (!values)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	map = ft_calloc(height + 1, sizeof(t_point *));
	if (!map)
	{
		write(2, "Error\n", 6);
		free(values);
		exit(1);
	}
	map->height = height;
	map->width = width;
	map->rows = ft_calloc(height + 1, sizeof(t_point *));
	i = 0;
	row = 0;
	while (values[i])
	{
		col = 0;
		map->rows[row] = ft_calloc(map->width + 1, sizeof(t_point));
		if (!map->rows[row])
			free_values(values);
		while (values[i][0] != '\n')
		{
			map->rows[row][col] = *make_point(row, col, ft_atoi(values[i]), WHITE);
			col++;
			i++;
		}
		row++;
		i++;
	}
	free(values);
	return (map);
}

int main() {
    char *filename = "../test_maps/10-2.fdf";
    t_map *map = make_map(filename);
	printf("Map created successfully.\n");

    if (map) {
        // printf("Map created successfully.\n");
        printf("Map height: %d\n", map->height);
        printf("Map width: %d\n", map->width);

        // Print the map
        for (int i = 0; i < map->height; i++) {
            for (int j = 0; j < map->width; j++) {
                printf("x: %d \n", map->rows[i][j].x);
				printf("y: %d \n", map->rows[i][j].y);
				printf("z: %d \n", map->rows[i][j].z);
				printf("row %d\n", i);
            }
            printf("\n##############\n");
        }

        // Free the map when done
        for (int i = 0; i < map->height; i++) {
            free(map->rows[i]);
        }
        free(map->rows);
        free(map);
    } else {
        printf("Failed to create map.\n");
    }

    return 0;
}
// cc make_map.c libft/ft_atoi.c libft/ft_split.c dimensions.c read_file.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c