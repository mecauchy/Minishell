/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:17:50 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 18:11:32 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (n);
	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]) && i + 1 < n)
		i ++;
	return (s1[i] - s2[i]);
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
// 	cp[0] = '4';
// 	cp[1] = '1';
// 	cp[2] = '\0';
// 	printf("%d", ft_strncmp(d, cp, 2));
// }