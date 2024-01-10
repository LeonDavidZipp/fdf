/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:22:54 by lzipp             #+#    #+#             */
/*   Updated: 2024/01/10 11:07:58 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_realloc(void *original, void *to_append, size_t orig_len,
// 		size_t app_len, size_t size)
// {
// 	void	*ptr;
// 	char	*cptr;
// 	size_t	total;
// 	int		i;

// 	total = (orig_len + app_len) * size;
// 	if ((orig_len != 0 && total / (orig_len + app_len) != size)
// 		|| (size != 0 && total / size != (orig_len + app_len)))
// 		return (NULL);
// 	ptr = ft_calloc(total + 1, size);
// 	cptr = (char *)ptr;
// 	i = -1;
// 	while (++i < (int)orig_len)
// 		cptr[i] = ((char *)original)[i];
// 	i = -1;
// 	while (++i < (int)app_len)
// 		cptr[orig_len + i] = ((char *)to_append)[i];
// 	free(original);
// 	original = ptr;
// 	free(ptr);
// 	free(cptr);
// 	return (original);
// }

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (malloc(0));
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memmove(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;
// 	char	*cptr;
// 	size_t	total;

// 	total = count * size;
// 	if ((count != 0 && total / count != size)
// 		|| (size != 0 && total / size != count))
// 		return (NULL);
// 	ptr = (void *)malloc(total);
// 	if (!ptr)
// 		return (NULL);
// 	cptr = (char *)ptr;
// 	while (total > 0)
// 	{
// 		*cptr = 0;
// 		cptr++;
// 		total--;
// 	}
// 	return (ptr);
// }

#include <stdio.h>
#include <string.h>
int main()
{
    // Test case 1: Appending a non-empty string to a non-empty string
    char *original1 = strdup("Hello");
    char *to_append1 = strdup(", World!");
    original1 = ft_realloc(original1, to_append1, strlen(original1), strlen(to_append1), sizeof(char));
    printf("Test 1 result: |%s|\n", original1);
	printf("strlen(result1): %zu\n", strlen(original1));
    free(original1);

    // Test case 2: Appending an empty string to a non-empty string
    char *original2 = strdup("Hello");
    char *to_append2 = strdup("");
    original2 = ft_realloc(original2, to_append2, strlen(original2), strlen(to_append2), sizeof(char));
    printf("Test 2 result: |%s|\n", original2);
	printf("strlen(result2): %zu\n", strlen(original2));
    free(original2);

    // Test case 3: Appending a non-empty string to an empty string
    // char *original3 = strdup("");
    // char *to_append3 = strdup(", World!");
    // char *result3 = ft_realloc(original3, to_append3, strlen(original3), strlen(to_append3), sizeof(char));
    // printf("Test 3 result: |%s|\n", result3);
	// printf("strlen(result3): %zu\n", strlen(result3));
    // free(result3);

    // // Test case 4: Appending an empty string to an empty string
    // char *original4 = strdup("");
    // char *to_append4 = strdup("");
    // char *result4 = ft_realloc(original4, to_append4, strlen(original4), strlen(to_append4), sizeof(char));
    // printf("Test 4 result: |%s|\n", result4);
	// printf("strlen(result4): %zu\n", strlen(result4));
    // free(result4);

    // // Test case 5: Appending a string to a NULL pointer
    // char *original5 = NULL;
    // char *to_append5 = strdup("Hello, World!");
    // char *result5 = ft_realloc(original5, to_append5, 0, strlen(to_append5), sizeof(char));
    // printf("Test 5 result: |%s|\n", result5);
	// printf("strlen(result5): %zu\n", strlen(result5));
    // free(result5);
	
	free(original1);
	free(original2);
	// free(original3);
	// free(original4);
	// free(original5);
	free(to_append1);
	free(to_append2);
	// free(to_append3);
	// free(to_append4);
	// free(to_append5);

    return 0;
}
