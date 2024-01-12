/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:01:00 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/12 14:56:16 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_hex(char *hex_char)
{
	int		i;

	if (hex_char[0] != '0' && hex_char[1] != 'x' && hex_char[1] != 'X')
		return (1);
	if (ft_strlen(hex_char) != 8)
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
	int		result;
	int		power;

	if (check_hex(hex_char) == 1)
		return (-1);
	result = 0;
	power = 1;
	len = ft_strlen(hex_char);
	while (--len >= 0 && hex_char[len] != 'x' && hex_char[len] != 'X')
	{
		if (hex_char[len] >= '0' && hex_char[len] <= '9')
			result += (hex_char[len] - '0') * power;
		else if (hex_char[len] >= 'A' && hex_char[len] <= 'F')
			result += (hex_char[len] - 'A' + 10) * power;
		else if (hex_char[len] >= 'a' && hex_char[len] <= 'f')
			result += (hex_char[len] - 'a' + 10) * power;
		else
			return (-1);
		power *= 16;
	}
	return (result);
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
	int		result;

	color = "0x00A000";
	printf("color: |%s|\n", color);
	printf("r: %d\n", int_to_r(ft_hex_to_int(color)));
	printf("g: %d\n", int_to_g(ft_hex_to_int(color)));
	printf("b: %d\n", int_to_b(ft_hex_to_int(color)));
	result = ft_hex_to_int(color);
	printf("result: %d\n", result);
	return (0);
}
