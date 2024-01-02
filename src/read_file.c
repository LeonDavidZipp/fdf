/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:25 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/02 13:07:42 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static char	*get_first_line(int fd, char **line)
{
	char	*lines;
	char	*empty_str;

	*line = get_next_line(fd);
	if (!line)
		return (NULL);
	empty_str = ft_strdup("");
	lines = ft_strjoin(empty_str, *line);
	free(*line);
	free(empty_str);
	return (lines);
}

static char	*get_lines(int fd, int *row_num)
{
	char	*line;
	char	*lines;
	char	*temp;

	lines = get_first_line(fd, &line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoin(lines, line);
		free(line);
		free(lines);
		if (!temp)
			return (NULL);
		lines = ft_strdup(temp);
		free(temp);
		if (!lines)
			return (NULL);
		*row_num += 1;
	}
	// *row_num = *row_num - 1; //REMOVE!!!
	return (lines);
}

char	*read_file(char *file_name)
{
	int		fd;
	int		row_num;
	char	*lines;

	fd = open(file_name, O_RDONLY);
	if (ft_strrncmp(file_name, ".fdf", 4) != 0 || fd < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	row_num = 1;
	lines = get_lines(fd, &row_num);
	close(fd);
	return (lines);
}

#include <stdio.h>
int	main(void)
{
	char	*lines;

	lines = read_file("/Users/lzipp/Desktop/42curriculum/fdf/test_maps/10-2.fd");
	printf("%s\n", lines);
	return (0);
}
