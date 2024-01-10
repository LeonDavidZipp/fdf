/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:29:26 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/09 13:05:14 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*cptr;
	size_t	total;

	total = count * size;
	if ((count != 0 && total / count != size)
		|| (size != 0 && total / size != count))
		return (NULL);
	ptr = (void *)malloc(total);
	if (!ptr)
		return (NULL);
	cptr = (char *)ptr;
	while (total > 0)
	{
		*cptr = 0;
		cptr++;
		total--;
	}
	return (ptr);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	// Test case 1: Allocate memory for 5 integers
// 	int *intArray = (int *)ft_calloc(5, sizeof(int));
// 	if (intArray != NULL)
// 	{
// 		for (int i = 0; i < 5; i++)
// 		{
// 			printf("%d ", intArray[i]); // Expected output: 0 0 0 0 0
// 		}
// 		printf("\n");
// 		free(intArray);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}
// 	Test case 2: Allocate memory for 3 double-precision floating-point numbers
// 	double *doubleArray = (double *)ft_calloc(3, sizeof(double));
// 	if (doubleArray != NULL)
// 	{
// 		for (int i = 0; i < 3; i++)
// 		{
// 			printf("%.2lf ", doubleArray[i]); // Expected output: 0.00 0.00 0.00
// 		}
// 		printf("\n");
// 		free(doubleArray);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}

// 	// Test case 3: Allocate memory for an array of characters
// 	char *charArray = (char *)ft_calloc(10, sizeof(char));
// 	if (charArray != NULL)
// 	{
// 		strcpy(charArray, "Hello");
// 		printf("%s\n", charArray); // Expected output: Hello
// 		free(charArray);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}

// 	return 0;
// }
