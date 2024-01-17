/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:16:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/17 12:11:38 by lzipp            ###   ########.fr       */
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

void	free_map(t_3d_point ***map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			free(map[i][j++]);
		free(map[i++]);
	}
	free(map);
}
