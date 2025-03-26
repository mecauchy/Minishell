/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:37:09 by vluo              #+#    #+#             */
/*   Updated: 2024/11/19 13:12:38 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i ++;
	}
	return (dest);
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
// int	ft_memcmp(const void *s1, const void *s2, size_t n)
// {
// 	const unsigned char	*so;
// 	const unsigned char	*st;
// 	size_t				i;

// 	if (n == 0)
// 		return (0);
// 	so = s1;
// 	st = s2;
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (so[i] != st[i])
// 			return (so[i] - st[i]);
// 		i ++;
// 	}
// 	return (0);
// }

// #include <stdio.h>
// int main(void)
// {
// 	void *s = malloc(sizeof(void) * 10);
// 	ft_bzero(s, 10);
// 	unsigned char *c = s;
// 	c[2] = 9;
// 	void *d = malloc(sizeof(void) * 10);
// 	ft_bzero(d, 10);
// 	d = ft_memcpy(d, s, 10);
// 	if (ft_memcmp(s, d, 10) != 0)
// 		printf("0");
// 	else
// 		printf("1");
// }