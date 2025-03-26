/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:22:31 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 11:27:44 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		p[n - 1] = c;
		n --;
	}
	return (s);
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
// 	void *d = malloc(sizeof(void) * 10);
// 	ft_memset(d, 2, 10);
// 	if (ft_memcmp(s, d, 10) != 0)
// 		printf("0");
// 	else
// 		printf("1");
// }