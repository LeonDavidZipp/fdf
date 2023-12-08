/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:20:25 by lzipp             #+#    #+#             */
/*   Updated: 2023/12/08 11:34:31 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static struct t_point	*make_point(int x, int y, int z)
{
	t_point		*point;

	point = ft_calloc(1, sizeof(t_point));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}
