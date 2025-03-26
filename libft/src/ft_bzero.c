/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:33:30 by vluo              #+#    #+#             */
/*   Updated: 2024/11/13 14:33:55 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i ++;
	}
	return ;
}

// #include <stdio.h>
// int	main(void)
// {
// 	void	*s = malloc(sizeof(void) * 10);
// 	unsigned char *c;
// 	size_t		n;

// 	n = 10;
// 	ft_bzero(s, 10);
// 	c = s;
// 	while(n > 0)
// 	{
// 		if (c[n - 1] != 0)
// 			printf("0");
// 		n --;
// 	}
// 	printf("1");
// }