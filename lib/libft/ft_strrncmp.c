/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:00:57 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/02 13:09:19 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	int			ind1;
	int			ind2;

	if (!s1 || !s2 || n == 0)
		return (0);
	ind1 = ft_strlen(s1) - 1;
	ind2 = ft_strlen(s2) - 1;
	while (n && s1[ind1] && (s1[ind1] == s2[ind2]))
	{
		if (n > 1)
		{
			--ind1;
			--ind2;
		}
		--n;
	}
	return ((int)(*(unsigned char *)&s1[ind1] - *(unsigned char *)&s2[ind2]));
}
