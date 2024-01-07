/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:13:02 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/07 15:00:17 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_width(char *lines)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!lines)
		return (0);
	while (lines[i + 1] != '\0')
	{
		if (lines[i] == ' ' && lines[i + 1] != ' ')
			len++;
		if (lines[i + 1] == '\n')
			break ;
		i++;
	}
	return (len);
}

int	get_height(char *lines)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (lines[i] != '\0')
	{
		if (lines[i] == '\n')
			len++;
		i++;
	}
	if (i > 0 && lines[i - 1] != '\n')
		len++;
	return (len);
}
