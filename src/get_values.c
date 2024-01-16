/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:29:27 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/16 16:29:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	**get_values(char *line)
{
	char		**temp;
	char		**values;
	int			len;
	int			i;

	temp = ft_split(line, ' ');
	if (!temp)
		return (NULL);
	len = 0;
	while (temp[len] && temp[len][0] != '\n')
		len++;
	values = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (++i < len)
	{
		values[i] = ft_strdup(temp[i]);
		if (!values[i])
		{
			free_values(values);
			free_values(temp);
		}
	}
	free_values(temp);
	return (values);
}
