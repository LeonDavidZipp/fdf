/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:32:58 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/08 15:02:31 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

#include <stdio.h>
static void	free_values(char **values)
{
	int		i;

	i = -1;

	// while (values[++i])
	// {
	// 	printf("string freed: |%s|\n", values[i]);
	// 	// free(values[i]);
	// }
	// printf("freeing values\n");
	free(values);
}

static void	free_map(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->height)
		free(map->rows[i]);
	free(map->rows);
	free(map);
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

static char	**remove_newlines(char **values)
{
	int		i;
	char	*temp;

	i = -1;
	while (values[++i])
	{
		if (values[i][0] == '\n')
		{
			temp = ft_strtrim(values[i], "\n");
			printf("string trimmed: |%s|\n", temp);
			free(values[i]);
			if (!temp)
			{
				free_values(values);
				return (NULL);
			}
			values[i] = temp;
			if (!values[i])
			{
				free_values(values);
				return (NULL);
			}
			free(temp);
		}
	}
	return (values);
}

static char **

static t_map	*generate_map(char **values)
{
	t_map	*map;

	if (!values)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	map = ft_calloc(1, sizeof(t_map));
	map->height = get_height(values);
	map->width = get_width(values);
	if (!map)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	map->rows = ft_calloc(map->height + 1, sizeof(t_point *));
	return (map);
}

static t_map	*fill_map(t_map *map, char **values)
{
	int		i;
	int		row;
	int		col;

	i = 0;
	row = 0;
	while (values[i])
	{
		col = 0;
		map->rows[row] = ft_calloc(map->width, sizeof(t_point));
		if (!map->rows[row])
		{
			free_values(values);
			free_map(map);
			write(2, "Error\n", 6);
			exit(1);
		}
		// while (values[i][0] != '\n')
		while (col < map->width)
		{
			printf("writing from index i: %d\n", i);
			// printf("---\n");
			map->rows[i / map->height][col] = *make_point(row, col, ft_atoi(values[i]), WHITE);
			// map->rows[row][col] = *make_point(row, col, ft_atoi(values[i]), WHITE);

			col++;
			i++;
		}
		row++;
	}
	return (map);
}

t_map	*make_map(char *filename)
{
	char	*lines;
	char	**values_step_1;
	char	**values_step_2;
	t_map	*map;

	lines = read_lines_from_file(filename);
	values_step_1 = ft_split(lines, ' ');
	int i = 0;
	while (values_step_1[i])
	{
		printf("string 1: |%s|\n", values_step_1[i]);
		// if (i % 10 == 0)
			// printf("----------\n");
		i++;
	}
	free(lines);
	// printf("have gotten here 1\n");
	if (!values_step_1)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	values_step_2 = remove_newlines(values_step_1);
	i = 0;
	while (values_step_2[i])
	{
		printf("string 2: |%s|\n", values_step_2[i]);
		i++;
	}
	// printf("have gotten here 2\n");
	// free_values(values_step_1);
	if (!values_step_2)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	map = generate_map(values_step_2);
	map = fill_map(map, values_step_2);
	free_values(values_step_2);
	return (map);
}

#include <stdio.h>
int main() {
    char *filename = "../test_maps/10-2.fdf";
    t_map *map = make_map(filename);
	// printf("Map created successfully.\n");

    if (map) {
        // printf("Map created successfully.\n");
        // printf("Map height: %d\n", map->height);
        // printf("Map width: %d\n", map->width);
        // Print the map
        for (int i = 0; i < map->height; i++) {
            for (int j = 0; j < map->width; j++) {
                // printf("x: %d \n", map->rows[i][j].x);
				// printf("y: %d \n", map->rows[i][j].y);
				// printf("z: %d \n", map->rows[i][j].z);
				// printf("row %d\n", i);
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

// t_map	*make_map_old(char *filename)
// {
// 	char	*lines;
// 	char	**values;
// 	int		i;
// 	int		row;
// 	int		col;
// 	int		width;
// 	int		height;
// 	t_map	*map;

// 	values = get_values(filename);
// 	width = get_width(values);
// 	height = get_height(values);
// 	map = ft_calloc(get_height(values) + 1, sizeof(t_point *));
// 	if (!map)
// 	{
// 		write(2, "Error\n", 6);
// 		free(values);
// 		exit(1);
// 	}
// 	map->height = height;
// 	map->width = width;
// 	map->rows = ft_calloc(height + 1, sizeof(t_point *));
// 	i = 0;
// 	row = 0;
// 	while (values[i])
// 	{
// 		col = 0;
// 		map->rows[row] = ft_calloc(map->width + 1, sizeof(t_point));
// 		if (!map->rows[row])
// 			free_values(values);
// 		while (values[i][0] != '\n')
// 		{
// 			map->rows[row][col] = *make_point(row, col, ft_atoi(values[i]), WHITE);
// 			col++;
// 			i++;
// 		}
// 		row++;
// 		i++;
// 	}
// 	free(values);
// 	return (map);
// }
