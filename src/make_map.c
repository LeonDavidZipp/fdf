/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:32:58 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/02 09:56:38 by lzipp            ###   ########.fr       */
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

static t_point	**make_map(char **lines)
{
	;
}

t_map	make_map(int fd)
{
	t_map		map;
	char		*line;
	char		**split_line;
	int			i;
	int			j;

	map.rows = ft_calloc(1, sizeof(t_point *));
	i = 0;
	while (get_next_line(fd, &line))
	{
		split_line = ft_split(line, ' ');
		map.rows[i] = ft_calloc(ft_arrlen(split_line) + 1, sizeof(t_point));
		j = 0;
		while (split_line[j])
		{
			map.rows[i][j] = *make_point(j, i, ft_atoi(split_line[j]), WHITE);
			j++;
		}
		map.rows[i][j] = *make_point(j, i, 0, WHITE);
		i++;
	}
	map.rows[i] = NULL;
	return (map);
}