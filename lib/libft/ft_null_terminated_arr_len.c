/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_terminated_arr_len.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:20:57 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/19 14:40:20 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_null_terminated_arr_len(void **arr)
{
	int		len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
