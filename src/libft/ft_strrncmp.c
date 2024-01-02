/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:00:57 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/02 13:08:29 by lzipp            ###   ########.fr       */
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


// int main() {
//     const char *testCases[10][2] = {
//         {"Hello, world!", "Hello, world!"},
//         {"Hello, world!", "Hello, World!"},
//         {"Hello, world!", "Hello, worlD"},
//         {"Hello, world!", "Hello, worl"},
//         {"Hello, world!", "Hello, world!!"},
//         {"Hello, world!", ""},
//         {"", "Hello, world!"},
//         {"", ""},
//         {"Hello, world!", "Hello, world! "},
//         {"Hello, world! ", "Hello, world!"}
//     };

//     size_t n = 5;

//     for (int i = 0; i < 10; i++) {
//         int result = ft_strrncmp(testCases[i][0], testCases[i][1], n);
//         printf("Result for test case %d: %d\n", i+1, result);
//     }
//     return 0;
// }
