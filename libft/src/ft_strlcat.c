/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:30:19 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 16:17:03 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	int		j;
	size_t	lendst;

	lendst = ft_strlen(dst);
	if (siz > ft_strlen(dst))
	{
		i = 0;
		j = 0;
		while (dst[i])
			i ++;
		while (src[j] && i < siz - 1)
			dst[i ++] = src[j ++];
		dst[siz] = 0;
	}
	if (siz < lendst)
		return (ft_strlen(src) + siz);
	return (ft_strlen(src) + lendst);
}
