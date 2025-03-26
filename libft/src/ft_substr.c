/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:16 by vluo              #+#    #+#             */
/*   Updated: 2024/11/19 12:59:48 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (len == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	while (s[start + i] && i < len)
		i ++;
	substr = malloc((i + 1) * sizeof(char));
	if (substr == 0)
		return (0);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i ++;
	}
	substr[i] = '\0';
	return (substr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *s = malloc(4 * sizeof(char));
// 	s[0] = 'o';
// 	s[1] = 'u';
// 	s[2] = 'i';
// 	s[3] = '\0';
// 	printf("%s", ft_substr(s, 1, 1));
// }
