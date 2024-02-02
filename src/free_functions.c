/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:16:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/02 11:55:05 by lzipp            ###   ########.fr       */
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

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			free(map[i][j]->projection);
			free(map[i][j]);
		}
		free(map[i]);
	}
	free(map);
}
#include <stdio.h>
void	free_app_data(t_app_data *app_data)
{
	printf("free app_data\n");
	// free(app_data->mlx);
	printf("free app_data->mlx\n");
	free(app_data->window);
	printf("free app_data->window\n");
	// free(app_data->image);
	printf("free app_data->image\n");
	free_map(app_data->map);
	printf("free app_data->map\n");
	free(app_data);
	printf("free app_data\n");
}
