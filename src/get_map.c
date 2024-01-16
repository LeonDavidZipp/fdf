/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:31:20 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/16 16:03:20 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	get_height(t_point **rows)
{
	int	len;

	len = 0;
	while (rows[len])
		len++;
	return (len);
}

#include <stdio.h>
t_map	*get_map(char *filename)
{
	// t_map	*map;
	t_point		***map;
	int			width;

	// map = malloc(sizeof(t_map));
	// if (!map)
	// {
	// 	write(2, "Error\n", 6);
	// 	exit(1);
	// }
	width = 0;
	map = get_rows(filename, &width);
	if (!map)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	// if (!map->rows)
	// {
	// 	write(2, "Error\n", 6);
	// 	free_rows(map->rows);
	// 	free_map(map);
	// 	exit(1);
	// }
	map->width = width;
	map->height = get_height(map->rows);
	return (map);
}

// cc get_map.c get_rows.c free_functions.c libft/ft_atoi.c color_conversion.c libft/ft_null_terminated_arr_len.c libft/ft_recalloc.c libft/ft_split.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft/ft_memmove.c
#include <stdio.h>

int	main(void)
{
	char	*filename;
	t_map	*map;
	int		i;
	int		j;

	filename = "../test_maps/t1.fdf";
	map = get_map(filename);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("x:%d y:%d z:%d color: %d\n", i, j, map->rows[i][j].z,
				map->rows[i][j].color);
			j++;
		}
		i++;
	}
	free_map(map);
	return (0);
}
