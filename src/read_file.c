/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:25 by lzipp             #+#    #+#             */
/*   Updated: 2023/12/08 17:57:57 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static char	*get_lines(int fd, int *row_num)
{
	char	*line;
	char	*lines;
	char	*temp;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	lines = ft_strjoin("", line);
	free(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoin(lines, line);
		free(lines);
		free(line);
		if (!temp)
			return (NULL);
		lines = ft_strdup(temp);
		free(temp);
		if (!lines)
			return (NULL);
		*row_num++;
	}
	return (lines);
}

char	*read_file(char *file_name)
{
	int		fd;
	int		row_num;
	char	*lines; 
	char	*line;

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
