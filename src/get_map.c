/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:31:20 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 18:53:13 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	get_height(t_point **rows)
{
	int		len;

	len = 0;
	while (rows[len])
		len++;
	return (len);
}

#include <stdio.h>
t_map	*get_map(char *filename)
{
	t_map	*map;

	int		width;
	map = malloc(sizeof(t_map));
	if (!map)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	width = 0;
	map->rows = get_rows(filename, &width);
	if (!map->rows)
	{
		write(2, "Error\n", 6);
		free_rows(map->rows);
		free_map(map);
		exit(1);
	}
	map->width = width;
	map->height = get_height(map->rows);
	printf("width: %d\n", map->width);
	printf("height: %d\n", map->height);
	return (map);
}

// cc get_map.c get_rows.c free_functions.c libft/ft_atoi.c color_conversion.c libft/ft_null_terminated_arr_len.c libft/ft_recalloc.c libft/ft_split.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft/ft_memmove.c
int main(void)
{
	char *filename = "../test_maps/basictest.fdf";
	t_map *map = get_map(filename);
	free_map(map);
	return (0);
}
