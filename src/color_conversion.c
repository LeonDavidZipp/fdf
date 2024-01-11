/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:01:00 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/11 23:27:25 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_hex(char *hex_char)
{
	int		i;

	if (hex_char[0] != '0')
		return (1);
	if (hex_char[1] != 'x' && hex_char[1] != 'X')
		return (1);
	i = 1;
	while (hex_char[++i])
	{
		if (!((hex_char[i] >= '0' && hex_char[i] <= '9')
				&& !(hex_char[i] >= 'A' && hex_char[i] <= 'F')
				&& !(hex_char[i] >= 'a' && hex_char[i] <= 'f')))
			return (1);
	}
	return (0);
}

int	ft_hex_to_int(char *hex_char)
{
	int		len;
	int		res;
	int		power;

	if (check_hex(hex_char))
		return (-1);
	len = 0;
	res = 0;
	power = 1;
	len = ft_strlen(hex_char);
	while (--len >= 0 && hex_char[len] != 'x')
	{
		if (hex_char[len] >= '0' && hex_char[len] <= '9')
			res += (hex_char[len] - '0') * power;
		else if (hex_char[len] >= 'A' && hex_char[len] <= 'F')
			res += (hex_char[len] - 'A' + 10) * power;
		else if (hex_char[len] >= 'a' && hex_char[len] <= 'f')
			res += (hex_char[len] - 'a' + 10) * power;
		else
			return (-1);
		power *= 16;
	}
	return (res);
}

int	ft_rgb_to_int(int r, int g, int b)
{
	int		res;

	res = 0;
	res += r * 256 * 256;
	res += g * 256;
	res += b;
	return (res);
}

int	ft_color_to_int(char *color)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	while (color[i] && color[i] != ',')
		i++;
	if (color[i] == ',')
		i++;
	r = ft_hex_to_int(&color[i]);
	while (color[i] && color[i] != ',')
		i++;
	if (color[i] == ',')
		i++;
	g = ft_hex_to_int(&color[i]);
	while (color[i] && color[i] != ',')
		i++;
	if (color[i] == ',')
		i++;
	b = ft_hex_to_int(&color[i]);
	return (ft_rgb_to_int(r, g, b));
}

#include <stdio.h>
int	main(void)
{
	char	*color;
	int		res;

	color = "0X00FF00";
	printf("color: |%s|\n", color);
	res = ft_hex_to_int(color);
	printf("res: %d\n", res);
	return (0);
}
