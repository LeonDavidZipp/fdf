/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:48:58 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 11:59:07 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	handle_not_valid(t_app_data *app_data)
{
	write(2, "Map is not valid\n", 17);
	free_app_data(app_data);
	exit(1);
}

void	check_map_valid(t_app_data *app_data)
{
	int		i;

	if (!app_data->map)
		handle_not_valid(app_data);
	i = 0;
	while (app_data->map[i])
	{
		if (!app_data->map[i][0])
			handle_not_valid(app_data);
		if (app_data->map[i + 1])
		{
			if (ft_null_terminated_arr_len((void **)app_data->map[i])
				!= ft_null_terminated_arr_len((void **)app_data->map[i + 1]))
				handle_not_valid(app_data);
		}
		i++;
	}
}
