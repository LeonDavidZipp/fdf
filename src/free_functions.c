/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:16:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/02 12:42:41 by lzipp            ###   ########.fr       */
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

void	free_app_data(t_app_data *app_data)
{
	free(app_data->window);
	free_map(app_data->map);
	free(app_data);
}
