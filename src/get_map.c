/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:31:20 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 17:51:07 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	get_width(t_point **rows)
{
	int		len;

	len = 0;
	while (rows[0][len])
		len++;
	return (len);
}

int	get_height(t_point **rows)
{
	int		len;

	len = 0;
	while (rows[len])
		len++;
	return (len);
}

t_map	*get_map(char *filename)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	map->rows = get_rows(filename);
	if (!map->rows)
	{
		write(2, "Error\n", 6);
		free_rows(map->rows);
		free_map(map);
		exit(1);
	}
	map->width = get_width(map->rows);
	map->height = get_height(map->rows);
	return (map);
}
