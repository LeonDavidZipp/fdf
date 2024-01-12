/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:16:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 19:33:43 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_values(char **values)
{
	int		i;

	i = -1;
	while (values[++i])
		free(values[i]);
	free(values);
}

void	free_rows(t_point **rows)
{
	int		i;

	i = -1;
	while (rows[++i])
		free(rows[i]);
	free(rows);
}

void	free_map(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->height)
		free(map->rows[i]);
	free(map->rows);
	free(map);
}
