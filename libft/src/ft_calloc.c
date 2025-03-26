/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:25:20 by vluo              #+#    #+#             */
/*   Updated: 2024/11/19 13:04:03 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size > 0 && SIZE_MAX / size < nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	void	*s = ft_calloc(10, 1);
// 	unsigned char *c;
// 	size_t		n;

// 	n = 10000;
// 	c = s;
// 	while(n > 0)
// 	{
// 		if (c[n - 1] != 0)
// 			printf("0");
// 		n --;
// 	}
// 	printf("1");
// }