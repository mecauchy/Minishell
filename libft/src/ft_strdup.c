/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:20:18 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:42:19 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dup == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *d = malloc(3 * sizeof(char));
// 	d[0] = '4';
// 	d[1] = '2';
// 	d[2] = '\0';
// 	char *dup = ft_strdup(d);
// 	for (int i = 0; i < 3; i ++)
// 	{
// 		if (dup[i] != d[i])
// 			printf("0");
// 	}
// 	printf("1");
// }