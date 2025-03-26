/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:24:15 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 18:12:38 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	int					u;

	u = c % 256;
	p = s;
	while (n > 0)
	{
		if (p[0] == u)
			return ((void *) p);
		n --;
		p ++;
		s ++;
	}
	return (0);
}

// void	ft_bzero(void *s, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*p;

// 	p = s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		p[i] = '\0';
// 		i ++;
// 	}
// 	return ;
// }
// #include <stdio.h>
// int main(void)
// {
// 	void *s = malloc(sizeof(void) * 10);
// 	ft_bzero(s, 10);
// 	unsigned char *c = s;
// 	c[2] = 9;
// 	if (ft_memchr(s, 9, 10) != 0)
// 		printf("1");
// 	else
// 		printf("0");
// }