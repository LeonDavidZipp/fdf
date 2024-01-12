/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:01:00 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 13:13:01 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_hex(char *hex_char)
{
	int		i;

	if (hex_char[0] != '0' && hex_char[1] != 'x' && hex_char[1] != 'X')
		return (1);
	i = 1;
	while (hex_char[++i])
	{
		if (!(hex_char[i] >= '0' && hex_char[i] <= '9')
			&& !(hex_char[i] >= 'A' && hex_char[i] <= 'F')
			&& !(hex_char[i] >= 'a' && hex_char[i] <= 'f'))
			return (1);
	}
	return (0);
}

int	ft_hex_to_int(char *hex_char)
{
	int		len;
	int		res;
	int		power;

	if (check_hex(hex_char) == 1)
		return (-1);
	res = 0;
	power = 1;
	len = ft_strlen(hex_char);
	while (--len >= 0 && hex_char[len] != 'x' && hex_char[len] != 'X')
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

int	int_to_r(int hex)
{
	return ((hex >> 16) & 0xFF);
}
int	int_to_g(int hex)
{
	return ((hex >> 8) & 0xFF);
}

int	int_to_b(int hex)
{
	return (hex & 0xFF);
}

#include <stdio.h>
int	main(void)
{
	char	*color;
	int		res;

	color = "0xFFFFFF";
	printf("color: |%s|\n", color);
	res = ft_hex_to_int(color);
	printf("res: %d\n", res);
	return (0);
}
