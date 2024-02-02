/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:01:00 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/02 19:53:32 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	check_hex(char *hex_char)
{
	int		i;

	if (hex_char[0] != '0' && hex_char[1] != 'x' && hex_char[1] != 'X')
		return (1);
	if (ft_strlen(hex_char) <= 2)
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

uint32_t	ft_hex_to_int(char *hex_char)
{
	int				len;
	uint32_t		result;
	uint32_t		power;

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
	result = result << 8;
	result += 0xFF;
	return (result);
}
