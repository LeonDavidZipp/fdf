/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:25 by lzipp             #+#    #+#             */
/*   Updated: 2023/12/08 13:48:27 by lzipp            ###   ########.fr       */
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

char	*read_file(char *file_name)
{
	int		fd;
	char	*line;
	char	*lines;

	fd = open(file_name, O_RDONLY);
	if (ft_strrncmp(file_name, ".fdf", 4) != 0 || fd < 0);
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	map_string = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		map = ft_strjoin(map, line);
		map = ft_strjoin(map, "\n");
	}
	close(fd);
	// spacer
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	row_num = 1;
	line = get_next_line(fd);
	lines = ft_strjoin("", line);
	free(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoin(lines, line);
		free(lines);
		lines = ft_strdup(temp);
		free(line);
		free(temp);
		row_num++;
	}
	close(fd);
	return (map);
}

t_map	make_map(int fd)
{
	t_map	map;
	char	*line;
	char	**split_line;
	int		i;
	int		j;

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