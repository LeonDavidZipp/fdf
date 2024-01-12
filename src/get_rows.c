/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rows.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:11 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 17:30:08 by lzipp            ###   ########.fr       */
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
			color = ft_hex_to_int(value_n_color[1]);
		row[i] = *make_point(row_num, i, ft_atoi(value_n_color[0]), color);
		free_values(value_n_color);
	}
}

t_point	*make_row(char *line, int row_num)
{
	t_point		*row;
	char		**values;
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

t_point	**get_rows(char *filename)
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
	rows = ft_calloc(1, sizeof(t_point *));
	while (line)
	{
		line = get_next_line(fd);
		rows = ft_recalloc(rows, (row_num + 1), sizeof(t_point *));
		rows[row_num] = make_row(line, row_num);
		row_num++;
	}
	close(fd);
	return (rows);
}

// cc make_map.c libft/ft_atoi.c libft/ft_split.c dimensions.c read_file.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
// cc get_rows.c free_functions.c libft/ft_atoi.c color_conversion.c libft/ft_null_terminated_arr_len.c libft/ft_recalloc.c libft/ft_split.c libft/ft_strdup.c libft/ft_strrncmp.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft/ft_memmove.c
// #include <stdio.h>
// int main(void)
// {
// 	char *filename = "../test_maps/basictest.fdf";
// 	int fd = open(filename, O_RDONLY);
// 	if (ft_strrncmp(filename, ".fdf", 4) != 0 || fd < 0)
// 	{
// 		write(2, "Error\n", 6);
// 		close(fd);
// 		exit(1);
// 	}
// 	t_point **map = get_rows(filename);
// 	printf("Map created successfully.\n");
// 	for (int i = 0; i < 10; i++)
// 	{
// 		for (int j = 0; j < 10; j++)
// 			printf("x:%d y:%d z:%d color: %d\n", i, j, map[i][j].z, map[i][j].color);
// 		printf("\n-------------\n\n");
// 	}
// }
