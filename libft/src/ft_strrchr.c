/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:03:32 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:40:41 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	if (ft_strchr(s, c) == 0)
		return (0);
	if (s[0] == '\0')
		return ((char *) s);
	if (ft_strchr(s, c) != 0 && ft_strchr(++s, c) == 0)
		return ((char *)--s);
	return (ft_strrchr(s, c));
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	printf("%s", ft_strrchr(argv[1], argv[2][0]));
// 	return (argc - argc);
// }
