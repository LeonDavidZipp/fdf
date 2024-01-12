/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:11 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 16:26:55 by lzipp            ###   ########.fr       */
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

void	process_values(char **values, t_point *row, int row_num, int len)
{
	int			i;
	int			color;
	char		**value_n_color;

	i = -1;
	while (++i < len)
	{
		value_n_color = ft_split(values[i], ',');
		if (!value_n_color)
		{
			free_values(values);
			free(row);
			return ;
		}
		color = WHITE;
		if (ft_null_terminated_arr_len(value_n_color) == 2)
			color = ft_hex_to_i(value_n_color[1]);
		row[i] = *make_point(row_num, i, ft_atoi(value_n_color[0]), color);
		free_values(value_n_color);
	}
}

t_point	*make_row(char *line, int row_num)
{
	t_point		*row;
	char		**values;
	char		**value_n_color;
	int			len;

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
	process_values(values, row, row_num, len);
	return (row);
}

t_map	*get_map(char *filename)
{
	int			fd;
	int			row_num;
	char		*line;
	t_point		**rows;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = ft_strdup("");
	row_num = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free_values(rows);
			close(fd);
			exit(1);
		}
		rows[row_num] = make_row(line, row_num);
		row_num++;
	}
	close(fd);
	return (rows);
}

// cc make_map.c libft/ft_atoi.c libft/ft_split.c dimensions.c read_file.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

t_map	*make_map_old(char *filename)
{
	
	char *filename = "../test_maps/10-2.fdf";
	int fd = open(filename, O_RDONLY);
	if (ft_strrncmp(filename, ".fdf", 4) != 0 || fd < 0)
	{
		write(2, "Error\n", 6);
		close(fd);
		exit(1);
	}
	t_point **map = get_map(filename)
	for 
}
