/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:26 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 18:10:32 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *) big);
	if (len == 0)
		return (0);
	i = 0;
	j = 0;
	while (big[i])
	{
		while (big[i + j] && little[j] && big[i + j] == little[j]
			&& i + j < len)
			j ++;
		if (little[j] == '\0')
			return ((char *) &big[i]);
		j = 0;
		i ++;
	}
	return (0);
}

// #include <stdio.h>
// #include <bsd/string.h>

// int main(void)
// {
// 	char *largestring = "Foo Bar Baz";
// 	char *smallstring = "Foo Bar Baz";
// 	char *ptr;
// 	char *p;

// 	ptr = ft_strnstr(largestring, smallstring, 6);
// 	p = strnstr(largestring, smallstring, 6);
// 	printf("%s\n", ptr);
// 	printf("%s", p);
// }
