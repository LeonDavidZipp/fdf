/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:26:22 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/16 16:43:44 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	check_input(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	if (ft_strrncmp(argv[1], ".fdf", 4) != 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

static int	check_open(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_point	***map;

	check_input(argc, argv);
	fd = check_open(argv[1]);
	map = make_map(fd);
	return (0);
}
