/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:26 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/11 22:58:41 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	*make_point(int x, int y, int z, int color)
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

static char	**get_values(char *line)
{
	char	**temp;
	char	**values;
	int		len;
	int		i;

	temp = ft_split(line, ' ');
	if (!temp)
		return (NULL);
	while (temp[len] && temp[len][0] != '\n')
		len++;
	values = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (++i < len)
		values[i] = temp[i];
	free(temp);
	return (values);
}

t_point	*make_row(char *line, int row_num)
{
	t_point		*row;
	char		**values;
	char		**value_n_color;
	int			len;
	int			i;

	values = get_values(line);
	if (!values)
		return (NULL);
	len = ft_null_terminated_arr_len(values);
	row = ft_calloc(len + 1, sizeof(t_point));
	if (!row)
	{
		free_values(values);
		return (NULL);
	}
	i = -1;
	while (++i < len)
	{
		value_n_color = ft_split(values[i], ',');
		if (!value_n_color)
		{
			free_values(values);
			return (NULL);
		}
		row[i] = *make_point(row_num, i, ft_atoi(value_n_color[i][0]), value_n_color[i][1]);
		free_values(value_n_color);
	}
	return (row);
}

t_map	*get_map(char *filename)
{
	int			fd;
	int			row_num;
	char		*line;
	t_point		*row;
	t_map		*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	line = ft_strdup("");
	row_num = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		row[row_num] = make_row(line, row_num);
	}
	close(fd);
	return (map);
}
