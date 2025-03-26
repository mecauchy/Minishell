/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:20:08 by vluo              #+#    #+#             */
/*   Updated: 2025/03/25 15:50:54 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == 0)
		return (0);
	i = 0;
	while (str[i])
		i ++;
	return (i);
}

// #include <stdlib.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *d = malloc(3 * sizeof(char));
// 	d[0] = '4';
// 	d[1] = '2';
// 	d[2] = '\0';
// 	printf("%zu", ft_strlen(d));
// }