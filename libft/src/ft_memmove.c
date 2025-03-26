/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:40:50 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 12:24:46 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	d = dst;
	s = src;
	if (d > s)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n --;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i ++;
		}
	}
	return (dst);
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
// 	d = ft_memmove(d, s, 10);
// 	if (ft_memcmp(s, d, 10) != 0)
// 		printf("0");
// 	else
// 		printf("1");
// }