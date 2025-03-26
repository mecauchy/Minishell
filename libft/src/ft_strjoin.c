/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:08:18 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:43:23 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*strj;

	strj = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (strj == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		strj[j ++] = s1[i ++];
	i = 0;
	while (s2[i])
		strj[j ++] = s2[i ++];
	strj[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (strj);
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	printf("%s", ft_strjoin(argv[1], argv[2]));
// 	return (argc - argc);
// }
