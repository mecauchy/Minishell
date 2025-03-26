/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:43:47 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 16:15:22 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	if (siz > 0)
	{	
		i = 0;
		while (i < siz - 1 && src[i])
		{
			dst[i] = src[i];
			i ++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}

// #include <stdlib.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *d = malloc(3 * sizeof(char));
// 	d[0] = '4';
// 	d[1] = '2';
// 	d[2] = '\0';
// 	char *cp = malloc(3 * sizeof(char));
// 	ft_strlcpy(cp, d, 3);
// 	printf("%s", cp);
// }