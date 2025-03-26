/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:24:10 by vluo              #+#    #+#             */
/*   Updated: 2024/11/19 12:58:47 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	size_t	i;

	i = 0;
	while (s1[i] && in_set(s1[i], set))
		i ++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	start = i;
	i = ft_strlen(s1) - 1;
	while (i > 0 && in_set(s1[i], set))
		i --;
	len = i - start + 1;
	return (ft_substr(s1, start, len));
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s = "      h a  ";
// 	char *set = " a";

// 	printf("|%s|", ft_strtrim(s, set));
// }