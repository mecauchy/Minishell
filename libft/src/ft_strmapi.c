/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:29:10 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:45:19 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*mapi;

	mapi = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (mapi == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		mapi[i] = f(i, s[i]);
		i ++;
	}
	mapi[i] = '\0';
	return (mapi);
}

// char f(unsigned int i, char c)
// {
// 	i++;
// 	c ++;
// 	return('a');
// }

// #include <stdio.h>
// int main(void)
// {
// 	char *s = "Hello";
// 	printf("%s", ft_strmapi(s, f));
// }